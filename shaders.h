#ifndef SHADERS_H
#define SHADERS_Hmake

namespace shaders
{

  std::string FRAG = "rect.frag";
  std::string VERT = "rect.vert";
  GLuint shading_program;

  void check_glew(GLenum err)
  {

    if (err != GLEW_OK){
        exit(1); // or handle the error in a nicer way
    }

    if (!GLEW_VERSION_2_1){  // check that the machine supports the 2.1 API.
      exit(1); // or handle the error in a nicer way
    }
  }


  const char *read_file(const char *filename)
  {
    long length = 0;
    char *result = NULL;
    FILE *file = fopen(filename, "r");
    if (file)
    {
      int status = fseek(file, 0, SEEK_END);
      if (status != 0)
      {
        fclose(file);
        return NULL;
      }
      length = ftell(file);
      status = fseek(file, 0, SEEK_SET);
      if (status != 0)
      {
        fclose(file);
        return NULL;
      }
      result = (char*)malloc((length + 1) * sizeof(char));
      if (result)
      {
        size_t actual_length = fread(result, sizeof(char), length, file);
        result[actual_length++] = '\0';
      }
      fclose(file);
      return result;
    }
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't read %s", filename);
    return NULL;
  }

  GLuint program_check(GLuint program)
  {
    //Error Checking
    GLint status;
    glValidateProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status)
    {
      GLint len;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
      if (len > 1)
      {
        char *log;
        log = (char*)malloc(len);
        glGetProgramInfoLog(program, len, &len, log);
        fprintf(stderr, "%s\n\n", log);
        free(log);
      }
      SDL_Log("Error linking shader default program.\n");
      return GL_FALSE;
    }
    return GL_TRUE;
  }

  GLuint compile_shader(GLenum type, GLsizei nsources, const char **sources)
  {

    GLuint shader;
    GLint success, len;
    GLsizei i, srclens[nsources];

    logg::print("function compile_shader:: after declaration", 0);

    for (i = 0; i < nsources; ++i)
    {
      srclens[i] = (GLsizei)strlen(sources[i]);
    }
    logg::print("function compile_shader:: after sources", 0);

    std::cout << type << std::endl;

    //logg::print("function compile_shader:: glCreateShader " + type, 0);
    shader = glCreateShader(type);


    logg::print("function compile_shader:: after glCreateShader", 0);

    glShaderSource(shader, nsources, sources, srclens);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
      if (len > 1)
      {
        char *log;
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, NULL, log);
        fprintf(stderr, "%s\n\n", log);
        free(log);
      }
      SDL_Log("Error compiling shader.\n");
    }
    SDL_Log("shader: %u", shader);
    return shader;
  }

    // loads a shader from file and returns the compiled shader
  GLuint get_shader(GLenum eShaderType, const char *filename)
  {

    const char *shaderSource = read_file(filename);

    logg::print("after read_file", 0);
    std::cout << eShaderType << std::endl;

    GLuint shader = compile_shader(eShaderType, 1, &shaderSource);
    logg::print("after compile_shader", 0);
    return shader;
  }

  //Get and build custom program from 2 files
  GLuint custom_shaders(const char *vsPath, const char *fsPath)
  {
    GLuint vertexShader;
    GLuint fragmentShader;

    logg::print("before get_shader",0);
    vertexShader = get_shader(GL_VERTEX_SHADER, vsPath);

    logg::print("after get vertex shader",0);

    fragmentShader = get_shader(GL_FRAGMENT_SHADER, fsPath);

    logg::print("after get frag shader",0);


    shading_program = glCreateProgram();
    logg::print("Shading program after create: " + std::to_string(shading_program),0);


    glAttachShader(shading_program, vertexShader);
    logg::print("Shading program after attach vertex: " + std::to_string(shading_program),0);

    glAttachShader(shading_program, fragmentShader);
    logg::print("Shading program after attach fragment: " + std::to_string(shading_program),0);

    glLinkProgram(shading_program);
    logg::print("Shading program after link: " + std::to_string(shading_program),0);

    //Error Checking
    GLuint status;
    status = program_check(shading_program);
    logg::print("CustomShader Status: " + std::to_string(status), 0);
    logg::print("Shading program after program check: " + std::to_string(shading_program),0);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (status == GL_FALSE){
      logg::print("CustomShaderException: Shader status is FALSE",0);
      return 0;
    };

    logg::print("Shading program before return: " + std::to_string(shading_program),0);
    return shading_program;
  }

}

#endif
