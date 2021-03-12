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
  SDL_Init(SDL_INIT_VIDEO);
  GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);



  //GPU_Target* WINDOW = GPU_Init(WINDOW_WIDTH, WINDOW_HEIGHT, GPU_DEFAULT_INIT_FLAGS);

  GPU_Target *WINDOW = GPU_InitRenderer(GPU_RENDERER_OPENGL_3, WINDOW_WIDTH, WINDOW_HEIGHT, GPU_DEFAULT_INIT_FLAGS);
  GPU_Image *field = GPU_LoadImage("field.png");

// dodaje te zmienne jako uniform do shadera 
  shaders::init("rain");
  shaders::add_variable("tex0");
  shaders::add_variable("tex1");
  shaders::add_variable("resolution");
  shaders::add_variable("globalTime");
  shaders::add_img("channel0.png");



  //shaders::add_img("ripper_spritesheet.png");

  while(RUNNING)
  {

    SDL_Event event;
    handle_events(event);

    GPU_Clear(WINDOW);

    // ma tylko zaslaniac, ten widok ma byc
    shaders::activate(); 
    GLfloat time = (GLfloat)SDL_GetTicks();
    //float resolution = WINDOW_HEIGHT;
    float resolution[2] = {(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT};
    //float offset[2] = {0.5, 0.5}; // ok jest git
    GPU_SetUniformf(shaders::get_var("globalTime"), time);
    shaders::set_img_shader();
    GPU_SetUniformfv(shaders::get_var("resolution"), 2, 1, resolution);
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