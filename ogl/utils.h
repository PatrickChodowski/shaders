
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

struct Vertex
{  
  double x_pos; 
  double y_pos;
  double z_pos;

  double r_col;
  double g_col;
  double b_col;
  double a_col;
};
// useful in buffer:
int COUNT_VERTEX_ATTRIBUTES = 7;
struct Vindex
{  
  int a; 
  int b;
  int c;
};



std::vector<Vertex> generate_vertices(int vertex_width, int vertex_height)
{
  int n_tiles = vertex_width*vertex_height; //80
  int n_vertices = (vertex_width + 1)*(vertex_height+1); //99

  double vertex_width_interval = 2/(double)vertex_width;
  double vertex_height_interval = 2/(double)vertex_height;
  std::vector<double> width_range = {};
  std::vector<double> height_range = {};
  double width_counter = -1.0;
  double height_counter = 1.0;
  width_range.push_back(width_counter);
  height_range.push_back(height_counter);
  // fill out width range
  for(int i=0; i < vertex_width; i++)
  {
    width_counter += vertex_width_interval;
    double rounded = truncf(width_counter * 10)/10;
    if(rounded == 0.0)
    {//looks ridiculous but I want positive 0
      rounded = 0;
    }
    width_range.push_back(rounded);
  }  

  // fill out height range
  for(int i=0; i < vertex_height; i++)
  {
    height_counter -= vertex_height_interval;
    double rounded = truncf(height_counter * 100)/100;
    if(rounded == 0.0)
    {//looks ridiculous but I want positive 0
      rounded = 0;
    }
    height_range.push_back(rounded);
  }  
  std::vector<Vertex> vertices = {};
  // for each height make a row 
  for(int h=0; h<height_range.size(); h++)
  {
    for(int w=0; w<width_range.size(); w++)
    {
      Vertex v;
      // positions
      v.x_pos = width_range[w];
      v.y_pos = height_range[h];
      v.z_pos = 0.0;

      // colors
      v.r_col = (double) rand()/RAND_MAX;
      v.g_col = 0.0f;
      v.b_col = 0.0f;
      v.a_col = 1.0f;



      vertices.push_back(v);
    } 
  }

  // for(int v=0; v< vertices.size(); v++)
  // {
  //   std::cout << vertices[v].x_pos << " " << vertices[v].y_pos << std::endl;
  // }
  return vertices;
}



std::vector<Vindex> generate_vindices(int vertex_width, int vertex_height)
{
  // this amount of indices I need (each tile = quad and then *2)

  int n_vindices = vertex_width*vertex_height*2; //160
  int n_vertices = (vertex_width + 1)*(vertex_height+1); //99

  // 0 1 11
  // 1 12 11

  // 1 2 12
  // 2 13 12
  std::vector<Vindex> vindices = {};
  int v_limit = n_vertices - (vertex_width+2); //99-(10+2) = 87
  int central_v = 0;

  while(central_v <= v_limit)
  {
    //create left part of the quad
    Vindex vi_l;
    vi_l.a = central_v;
    vi_l.b = central_v+1;
    vi_l.c = central_v+vertex_width+1;
    vindices.push_back(vi_l);

    //create right part of the quad
    Vindex vi_r;
    vi_r.a = central_v+1;
    vi_r.b = central_v+vertex_width+1;
    vi_r.c = central_v+vertex_width;
    vindices.push_back(vi_r);
    central_v += 1;
  }

  return vindices;
}