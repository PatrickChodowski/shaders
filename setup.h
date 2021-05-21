

#include <GL/glew.h>


#ifdef TARGET_OS_MAC
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

#ifdef __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

// glm includes
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"




/// woooooo
// http://docs.gl/

int TILE_DIM = 96;

// how many quads to show in opengl
int WINDOW_VERTEX_WIDTH = 10;
int WINDOW_VERTEX_HEIGHT = 8;
int MAP_VERTEX_WIDTH = 20;
int MAP_VERTEX_HEIGHT = 16;

std::string TEMP_LEVEL_NAME = "test";

int WINDOW_WIDTH = WINDOW_VERTEX_WIDTH*TILE_DIM;
int WINDOW_HEIGHT = WINDOW_VERTEX_HEIGHT*TILE_DIM;
int MAP_WIDTH = TILE_DIM * MAP_VERTEX_WIDTH;
int MAP_HEIGHT = TILE_DIM * MAP_VERTEX_HEIGHT;

int LOGGING = 0;

std::string LEVEL_NAME = "test";
std::string CURRENT_SHADER = "canvas";

//Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
Uint32 flags = SDL_WINDOW_OPENGL;

const Uint8 *KEYBOARD = SDL_GetKeyboardState(NULL);
bool RUNNING = true;
#include "utils/logging.h"
#include "ogl/utils.h"
#include "ogl/textures.h"
#include "utils/quads.h"



#include "ogl/shaders.h"
#include "ogl/buffer.h"

// #include "World.h"

int CAMERA_SPEED = 20;
int CAMERA_X = 0;
int CAMERA_Y = 0;
int ZOOM = 0;
int ZOOM_SPEED = 100;

bool CAMERA_CENTRIC = true;
int MOVE_CAMERA_X = 0;
int MOVE_CAMERA_Y = 0;




  void handle_events(SDL_Event event)
  // subsystem for handling players input
  {
    CAMERA_X = 0;
    CAMERA_Y = 0;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_MOUSEWHEEL:
        if(event.wheel.y > 0) {ZOOM += ZOOM_SPEED;}
        else if(event.wheel.y < 0){ZOOM -= ZOOM_SPEED;}
        break;
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
