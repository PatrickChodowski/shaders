

SDL_Window *WINDOW = SDL_CreateWindow("test shaders",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH,
                                      WINDOW_HEIGHT,
                                      0);


SDL_Renderer *RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
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
  while(RUNNING)
  {

    SDL_Event event;
    handle_events(event);
    SDL_Delay(1000 / 60);
  }


  return 0;
}