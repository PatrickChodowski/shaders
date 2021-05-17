#include "setup.h"



/// time to allow texture book and variable texture types

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

  std::vector<tiles::Tile> level_map = tiles::load_level("test", MAP_VERTEX_WIDTH, MAP_VERTEX_HEIGHT, TILE_DIM);



  std::map<int, Vertex> VERTICES = generate_vertices(MAP_VERTEX_WIDTH, MAP_VERTEX_HEIGHT, TILE_DIM);
  glm::mat4 MVP = generate_mvp();
  std::vector<Quad> QUADS = generate_quad_list(MAP_VERTEX_WIDTH, MAP_VERTEX_HEIGHT);
  std::vector<Vindex> VINDICES = generate_vindices(QUADS);

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
    glUniformMatrix4fv(glGetUniformLocation(shaders::shader_map[CURRENT_SHADER], "mvp"), 1, GL_FALSE, glm::value_ptr(MVP));
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