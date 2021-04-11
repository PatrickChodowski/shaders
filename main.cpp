
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
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
}; 


    float colors[] = {
      1.0,  0.0,  0.0, //red
      0.0,  1.0,  0.0, //green
      0.0,  0.0,  1.0, //blue
      1.0,  1.0,  1.0  //white
    };


unsigned int VBO, VAO, EBO;
glGenVertexArrays(1, &VAO);
// glGenBuffers(1, &VBO_colors);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
// glBufferData(GL_ARRAY_BUFFER, sizeof(VBO_colors), colors, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VBO_colors), 0);
// glEnableVertexAttribArray(1);

// glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// glEnableVertexAttribArray(2);

    // create a vertex array object
    // A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects and is 
    // designed to store the information for a complete rendered object. 
    // In our example this is a diamond consisting of four vertices as well as a color for each vertex.
    // The shaders receive input data from our VAO through a process of attribute binding, 
    // allowing us to perform the needed computations to provide us with the desired results.
    // create a vertex buffer object
    // A Vertex Buffer Object (VBO) is a memory buffer in the high speed memory of your video card designed to hold information about vertices. 
    // In our example we have two VBOs, one that describes the coordinates of our vertices and another that describes 
    // the color associated with each vertex. VBOs can also store information such as normals, texcoords, indicies, etc.
    // textures::load_texture("field.png", 100, 100, 3);

  logg::print("Before shading program",0);
  GLuint shading_program = shaders::custom_shaders(shaders::VERT.c_str(), shaders::FRAG.c_str());
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

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(WINDOW);
    SDL_Delay(1000 / 60);
  }

  glDeleteProgram(shading_program);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  // glDeleteBuffers(1, &VBO_vertices);
  glDeleteBuffers(1, &EBO);




  SDL_GL_DeleteContext(GLCONTEXT); 
  SDL_DestroyWindow(WINDOW);
  SDL_Quit();


  return 0;
}