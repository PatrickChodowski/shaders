
// XD moj kod
// absolutnie moj kod
#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GlCall(x) GlClearError();x;ASSERT(GlLogCall(#x, __FILE__, __LINE__));

static void GlClearError()
{
  while(glGetError() != GL_NO_ERROR);
}

static bool GlLogCall(const char* function, const char* file, int line)
{ 
  while(GLenum error = glGetError())
  {
    std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << " " << line << std::endl;
    return false;
  }
  return true;
}

glm::mat4 generate_mvp()
{
  // glm::mat4 proj = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f);

  glm::mat4 proj = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  glm::mat4 mvp = proj*view*model;
  return mvp;
}
