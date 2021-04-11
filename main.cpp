
// g++ main.cpp -o game  -lSDL2 -lSDL2_image -lGL -lGLEW
// https://learnopengl.com/Getting-started/Shaders
// https://learnopengl.com/Getting-started/Textures
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <ctime>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//https://github.com/Acry/SDL2-OpenGL/blob/master/src/3a2.c
//https://github.com/Acry/SDL2-OpenGL/blob/master/src/2.c

int WINDOW_WIDTH = 896;
int WINDOW_HEIGHT = 768;
int LOGGING = 0;

//Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
Uint32 flags = SDL_WINDOW_OPENGL;

const Uint8 *KEYBOARD = SDL_GetKeyboardState(NULL);
bool RUNNING = true;
#include "utils/logging.h"
#include "utils/textures.h"
#include "shaders.h"



  void handle_events(SDL_Event event)
  // subsystem for handling players input
  {

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        RUNNING = false;
        break;
      };
    };
  };


int main()
{


  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_Window *WINDOW = SDL_CreateWindow("test shaders",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          flags);

  SDL_GLContext GLCONTEXT = SDL_GL_CreateContext(WINDOW);
  Uint32 current_sdl_gl = SDL_GL_MakeCurrent(WINDOW, GLCONTEXT);
  if(current_sdl_gl != 0)
  {
    std::string error_text = SDL_GetError();
    logg::print("SDL_GL Make Current failed: " + error_text,0);
  }

  SDL_GL_SetSwapInterval(1);
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  GLenum err = glewInit();
  shaders::check_glew(err);

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f, // bottom left
        -0.5f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  }; 

  float tex_coords[] = {
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f
  };

  float light_coords[2] = {0.0f, 0.0f};

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


  unsigned int texture1 = textures::load_texture("field.png", 300, 300, 3);

  logg::print("Before shading program",0);
  GLuint shading_program = shaders::custom_shaders(shaders::VERT.c_str(), shaders::FRAG.c_str());

  glUniform1i(glGetUniformLocation(shading_program, "texture1"), 0);
  glUniform2fv(glGetUniformLocation(shading_program, "LightCoord"), 2, light_coords);


  logg::print("After shading program",0);
	glReleaseShaderCompiler();
  logg::print("After gl relase shader compiler",0);


  if (shading_program == 0){
    logg::print("Shading program is "+ std::to_string(shading_program), 0);
		RUNNING = 0;
	} else {
		SDL_Log("Using program %d\n", shading_program);
  }
	if (glGetError()!=0)
  {
		SDL_Log("glError: %#08x\n", glGetError());
  }

  while(RUNNING)
  {
    SDL_Event event;
    handle_events(event);
    glClearColor(0.2f,0.1f,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shading_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(WINDOW);
    SDL_Delay(1000 / 60);
  }

  glDeleteProgram(shading_program);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  SDL_GL_DeleteContext(GLCONTEXT); 
  SDL_DestroyWindow(WINDOW);
  SDL_Quit();


  return 0;
}