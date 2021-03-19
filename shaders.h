#ifndef SHADERS_H
#define SHADERS_H

namespace shaders
{

  std::string FRAG = "light.frag";
  std::string VERT = "light.vert";

  SDL_GLContext GLCONTEXT = SDL_GL_CreateContext(WINDOW);
  GLuint shading_program;
  // extern void glGetProgramInfoLog(GLuint, GLsizei, GLsizei *, GLchar *);

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

    for (i = 0; i < nsources; ++i)
      srclens[i] = (GLsizei)strlen(sources[i]);

    shader = glCreateShader(type);
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
    GLuint shader = compile_shader(eShaderType, 1, &shaderSource);
    return shader;
  }

  //Get and build custom program from 2 files
  GLuint custom_shaders(const char *vsPath, const char *fsPath)
  {
    GLuint vertexShader;
    GLuint fragmentShader;

    vertexShader = get_shader(GL_VERTEX_SHADER, vsPath);
    fragmentShader = get_shader(GL_FRAGMENT_SHADER, fsPath);

    shading_program = glCreateProgram();

    glAttachShader(shading_program, vertexShader);
    glAttachShader(shading_program, fragmentShader);

    glLinkProgram(shading_program);

    //Error Checking
    GLuint status;
    status = program_check(shading_program);
    if (status == GL_FALSE)
      return 0;
    return shading_program;
  }

}

#endif
