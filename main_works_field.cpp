#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include <SDL2/SDL_gpu.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include "shaders.h"
#include <GL/gl.h>
#include <GL/glu.h>

// g++ main.cpp -o game  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gpu -lGL
//https://shader-tutorial.dev/advanced/transparency/

// install:
// move to sdl_gpu/sdl-gpu
// this install in  usr/include/SDL2/
//cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/usr 
//make
//sudo make install


// g++ main.cpp -o game  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gpu
// https://glusoft.com/tutorials/sdl2/use-glsl-shader
// https://grimfang4.github.io/sdl-gpu/group__ShaderInterface.html

int WINDOW_WIDTH = 896;
int WINDOW_HEIGHT = 768;
bool RUNNING = true;


const Uint8 *KEYBOARD = SDL_GetKeyboardState(NULL);


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
  //SDL_Init(SDL_INIT_VIDEO);
  //GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

  GPU_Target* WINDOW = GPU_Init(WINDOW_WIDTH, WINDOW_HEIGHT, GPU_DEFAULT_INIT_FLAGS);

  //GPU_Target *WINDOW = GPU_InitRenderer(GPU_RENDERER_OPENGL_3, WINDOW_WIDTH, WINDOW_HEIGHT, GPU_DEFAULT_INIT_FLAGS);
  GPU_Image *field = GPU_LoadImage("field.png");

  //GPU_SetBlending(field, true); 

  //GPU_SetBlendFunction(field, GPU_FUNC_SRC_COLOR, GPU_FUNC_DST_COLOR, GPU_FUNC_SRC_ALPHA, GPU_FUNC_DST_ALPHA);


// dodaje te zmienne jako uniform do shadera 
  shaders::init("light");
  shaders::add_variable("resolution");
  shaders::add_variable("offset");
  shaders::add_variable("tex0");
  shaders::add_img("field.png");


  while(RUNNING)
  {

    SDL_Event event;
    handle_events(event);
    GPU_Clear(WINDOW);
    
    shaders::activate(); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation (GL_FUNC_ADD);
    GLfloat time = (GLfloat)SDL_GetTicks();
    float resolution[2] = {(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT};
    float offset[2] = {0.5, 0.5}; // ok jest git

    GPU_SetUniformf(shaders::get_var("globalTime"), time);
    GPU_SetUniformfv(shaders::get_var("resolution"), 2, 1, resolution);
    GPU_SetUniformfv(shaders::get_var("offset"), 2, 1, offset);
    shaders::set_img_shader("tex0");
    
    GPU_Blit(field, NULL, WINDOW, field->w / 2.f, field->h / 2.f);
      
    GPU_DeactivateShaderProgram(); 
    GPU_Flip(WINDOW);
    SDL_Delay(1000 / 60);
  }


  GPU_FreeImage(shaders::img);
  GPU_FreeImage(field);
  GPU_Quit();
  return 0;
}