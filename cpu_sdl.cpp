#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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


int WINDOW_WIDTH = 896;
int WINDOW_HEIGHT = 768;
int LOGGING = 1;

SDL_Window *WINDOW = SDL_CreateWindow("test shaders",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH,
                                      WINDOW_HEIGHT,
                                      0);


SDL_Renderer *RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
const Uint8 *KEYBOARD = SDL_GetKeyboardState(NULL);
bool RUNNING = true;
#include "utils/logging.h"
#include "utils/textures.h"


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

  textures::init();
  while(RUNNING)
  {
    SDL_Event event;
    handle_events(event);


    SDL_RenderClear(RENDERER);

    SDL_Rect obj_sprite;
    obj_sprite.h=WINDOW_HEIGHT;
    obj_sprite.w=WINDOW_WIDTH;
    obj_sprite.x=0;
    obj_sprite.y=0;
    SDL_RenderCopy(RENDERER,
                   textures::field,
                   NULL,
                   &obj_sprite);

    SDL_RenderPresent(RENDERER);
    SDL_Delay(1000 / 60);
  }

    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();


  return 0;
}