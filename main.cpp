
// g++ main.cpp -o game  -lSDL2 -lSDL2_image -lGL -lGLEW
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


//https://github.com/Acry/SDL2-OpenGL/blob/master/src/3a2.c
//https://github.com/Acry/SDL2-OpenGL/blob/master/src/2.c

int WINDOW_WIDTH = 896;
int WINDOW_HEIGHT = 768;
int LOGGING = 0;


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

GLenum err = glewInit();


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

  shaders::check_glew();

  SDL_GLContext glContext = SDL_GL_CreateContext(WINDOW);
  textures::init();

  logg::print("Before shading program",0);
  GLuint shading_program = shaders::custom_shaders(shaders::VERT.c_str(), shaders::FRAG.c_str());
  logg::print("After shading program",0);
	glReleaseShaderCompiler();
  logg::print("After gl relase shader compiler",0);


  if (shading_program == 0){
    logg::print(std::to_string(shading_program), 0);
		RUNNING = 0;
	} else
		SDL_Log("Using program %d\n", shading_program);
	
	if (glGetError()!=0)
		SDL_Log("glError: %#08x\n", glGetError());
	
	glUseProgram(shading_program);

  logg::print("before while loop",0);
  std::cout << RUNNING << std::endl;
  while(RUNNING)
  {
    SDL_Event event;
    handle_events(event);
    // SDL_RenderClear(RENDERER);

    // SDL_Rect obj_sprite;
    // obj_sprite.h=WINDOW_HEIGHT;
    // obj_sprite.w=WINDOW_WIDTH;
    // obj_sprite.x=0;
    // obj_sprite.y=0;
    // SDL_RenderCopy(RENDERER,
    //                textures::field,
    //                NULL,
    //                &obj_sprite);

    // SDL_RenderPresent(RENDERER);
    glClear(GL_COLOR_BUFFER_BIT);
		glRectf(-1.0, -1.0, 1.0, 1.0);
		SDL_GL_SwapWindow(WINDOW);
    SDL_Delay(1000 / 60);
  }

    SDL_DestroyRenderer(RENDERER);
    SDL_GL_DeleteContext(glContext); 
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();


  return 0;
}