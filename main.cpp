#include "setup.h"

int main()
{
  textures::init();
  std::vector<quads::Quad> QUADS  = quads::init();

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

  buffer::init(QUADS);
  shaders::shader_map["light_radius_shading_program"] = shaders::custom_shaders("light_radius_rect");
  shaders::shader_map["canvas"] = shaders::custom_shaders("canvas");

  glReleaseShaderCompiler();
  float light_coords[2] = {(float)(WINDOW_WIDTH/2), (float)(WINDOW_HEIGHT/2)};

  unsigned int texture0 = textures::load(0, "./assets/dungeon_spritesheet.png", 256, 64, 4);
  unsigned int texture1 = textures::load(1, "./assets/redripper_spritesheet.png", 64, 64, 4);
  textures::bind(texture0, 0);
  textures::bind(texture1, 1);

  while(RUNNING)
  {
    SDL_Event event;
    handle_events(event);

    light_coords[0] += CAMERA_X;
    light_coords[1] += CAMERA_Y;

    glClear(GL_COLOR_BUFFER_BIT);
    glUniform2f(glGetUniformLocation(shaders::shader_map[CURRENT_SHADER], "LightCoord"), light_coords[0], light_coords[1]);
    int samplers[2] = {0,1};
    glUniform1iv(glGetUniformLocation(shaders::shader_map[CURRENT_SHADER], "textures"), 2, samplers);

    glm::mat4 MVP = generate_mvp(ZOOM);
    glUniformMatrix4fv(glGetUniformLocation(shaders::shader_map[CURRENT_SHADER], "mvp"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUseProgram(shaders::shader_map[CURRENT_SHADER]);


    glBindVertexArray(buffer::VAO); 
    // batch drawing:
    glDrawElements(GL_TRIANGLES, QUADS.size()*6, GL_UNSIGNED_INT, nullptr);

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