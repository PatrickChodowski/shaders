
// standard libraries/dependencies
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

// Include GLEW. Always include it before gl.h 
#include <GL/glew.h>

// using sdl2 as main event handler
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// opengl added
#include <OpenGL/gl.h>


int WINDOW_WIDTH = 896;
int WINDOW_HEIGHT = 768;
bool RUNNING = true;

SDL_Window *WINDOW = SDL_CreateWindow("OpenGL x SDL2 test",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH,
                                      WINDOW_HEIGHT,
                                      0);

// get utils
#include "utils.h"
#include "new_shader.h"



int main()
{   
    // init sdl
     SDL_Init(SDL_INIT_VIDEO);
     SDL_GLContext GLCONTEXT = SDL_GL_CreateContext(WINDOW);
     GLuint programID = shaders::LoadShaders( "test.vert", "test.frag" );
     while(RUNNING)
     {
         SDL_Event event;
         utils::handle_events(event);
         utils::display_stuff(programID);
     }

    std::cout<<"main done" << std::endl;

    // close sdl
    SDL_Quit();
    return 0;
}