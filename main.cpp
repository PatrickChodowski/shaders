
// note(todo:) if mac os then OpenGL/ else GL/ for gl, glu
// note: glut not needed?
// makefile for mac: g++ -std=c++11 main.cpp -o game -lSDL2 -lSDL2_image -lGLEW -framework OpenGL

#include <GL/glew.h>
// #include <GL/gl.h>
#include <OpenGL/gl.h>
// #include <GL/glu.h>
#include <OpenGL/glu.h>
// #include <GL/glut.h>
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
#include <signal.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/// woooooo
// http://docs.gl/

int TILE_DIM = 96;

// how many quads to show in opengl
int VERTEX_WIDTH = 10;
int VERTEX_HEIGHT = 8;

int WINDOW_WIDTH = VERTEX_WIDTH*TILE_DIM;
int WINDOW_HEIGHT = VERTEX_HEIGHT*TILE_DIM;
int LOGGING = 0;
int VECTOR_HEIGHT = 24;
int VECTOR_WIDTH = 28;
int MAP_WIDTH = TILE_DIM * VECTOR_WIDTH;
int MAP_HEIGHT = TILE_DIM * VECTOR_HEIGHT;

std::string LEVEL_NAME = "test";
std::string CURRENT_SHADER = "canvas";

//Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
Uint32 flags = SDL_WINDOW_OPENGL;

const Uint8 *KEYBOARD = SDL_GetKeyboardState(NULL);
bool RUNNING = true;
#include "utils/logging.h"

#include "ogl/utils.h"
#include "ogl/textures.h"
#include "ogl/shaders.h"
#include "ogl/buffer.h"

// #include "World.h"

int CAMERA_SPEED = 10;
int CAMERA_X = 0;
int CAMERA_Y = 0;





  void handle_events(SDL_Event event)
  // subsystem for handling players input
  {
    CAMERA_X = 0;
    CAMERA_Y = 0;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        RUNNING = false;
        break;

        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
          CAMERA_X -= CAMERA_SPEED;
          break;
        case SDLK_RIGHT:
          CAMERA_X += CAMERA_SPEED;
          break;
        case SDLK_UP:
          CAMERA_Y += CAMERA_SPEED;
          break;
        case SDLK_DOWN:
          CAMERA_Y -= CAMERA_SPEED;
          break;
        case SDLK_l:
          CURRENT_SHADER = "light_radius_shading_program";
          break;
        case SDLK_g:
          CURRENT_SHADER = "canvas";
          break;
        }



      };
    };
  };


int main()
{

  // std::vector<Vertex> VERTICES = generate_vertices(VERTEX_WIDTH, VERTEX_HEIGHT);
  // std::vector<Vindex> VINDICES = generate_vindices(VERTEX_WIDTH, VERTEX_HEIGHT);

  std::vector<Vertex> VERTICES = generate_vertices_offsets(VERTEX_WIDTH, VERTEX_HEIGHT);
  std::vector<Quad> QUADS = generate_quad_list(VERTEX_WIDTH, VERTEX_HEIGHT);
  std::vector<Vindex> VINDICES = generate_vindices_offsets(QUADS);


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
  buffer::init(VERTICES, VINDICES);
  textures::init();

  //// level data
  //world::init_lvl(LEVEL_NAME);

  unsigned int texture1 = textures::load(1, "./assets/dungeon_spritesheet.png", 256, 64, 4);
  textures::bind(texture1, 0);

  shaders::shader_map["light_radius_shading_program"] = shaders::custom_shaders("light_radius_rect");
  shaders::shader_map["canvas"] = shaders::custom_shaders("canvas");

  glReleaseShaderCompiler();
  float light_coords[2] = {(float)(WINDOW_WIDTH/2), (float)(WINDOW_HEIGHT/2)};
  //float resolution[2] = {(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT};

  while(RUNNING)
  {
    SDL_Event event;
    handle_events(event);

    light_coords[0] += CAMERA_X;
    light_coords[1] += CAMERA_Y;

    glClear(GL_COLOR_BUFFER_BIT);
    glUniform2f(glGetUniformLocation(shaders::shader_map[CURRENT_SHADER], "LightCoord"), light_coords[0], light_coords[1]);
    glUniform1i(glGetUniformLocation(shaders::shader_map[CURRENT_SHADER], "texture1"), 0);
    glUseProgram(shaders::shader_map[CURRENT_SHADER]);

    textures::bind(texture1, 0);

    glBindVertexArray(buffer::VAO); 
    // batch drawing:
    glDrawElements(GL_TRIANGLES, VINDICES.size()*3, GL_UNSIGNED_INT, nullptr);

		SDL_GL_SwapWindow(WINDOW);
    SDL_Delay(1000 / 60);
  }

  shaders::drop();
  buffer::drop();
  SDL_GL_DeleteContext(GLCONTEXT); 
  SDL_DestroyWindow(WINDOW);
  SDL_Quit();


  return 0;
}