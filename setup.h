
// note(todo:) if mac os then OpenGL/ else GL/ for gl, glu
// note: glut not needed?
// makefile for mac: g++ -std=c++11 main.cpp -o game -lSDL2 -lSDL2_image -lGLEW -framework OpenGL

#include <GL/glew.h>
// #include <GL/gl.h>
#include <OpenGL/gl.h>
// #include <GL/glu.h>
#include <OpenGL/glu.h>



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

#include "utils/tiles.h"


#include "ogl/textures.h"
#include "ogl/shaders.h"
#include "ogl/buffer.h"

// #include "World.h"

int CAMERA_SPEED = 20;
int CAMERA_X = 0;
int CAMERA_Y = 0;