
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
  // info send to GPU:
  double x_pos; 
  double y_pos;
  double z_pos;

  double r_col;
  double g_col;
  double b_col;
  double a_col;

  double tile_type;
  double tex_coord_x;
  double tex_coord_y;

  /// not counted as VERTEX ATTRIBUTES - yet
  int quad_id;
  int vertex_id;
};
// useful in buffer:
int COUNT_VERTEX_ATTRIBUTES = 10;
struct Vindex
{  
  int a; 
  int b;
  int c;
};

struct Quad
{
  int quad_id;
  int top_left;
  int top_right;
  int bottom_left;
  int bottom_right;
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
      v.g_col = (double) rand()/RAND_MAX;
      v.b_col = (double) rand()/RAND_MAX;
      v.a_col = 1.0f;


      // tile type
      v.tile_type = 10;

      // (0,1), (1, 1)
      // (0,0), (1, 0)

      float tex_coord_x = 0;
      float tex_coord_y = 0;
      if(w%2 == 1){tex_coord_x = 0.249;};
      if(h%2 == 1){tex_coord_y = 1;};

      v.tex_coord_x = tex_coord_x;
      v.tex_coord_y = tex_coord_y;

      vertices.push_back(v);
      // if 
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
  int n_rows = (vertex_height+1);

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
    vi_r.b = central_v+vertex_width+2;
    vi_r.c = central_v+vertex_width+1;
    vindices.push_back(vi_r);

    int NROW = std::floor((float)(central_v+1)/(vertex_width+1))+1;
    // move by 2 at the end of the quads row
    if ((central_v+1) == ((NROW*vertex_width) + (NROW-1)))
    {
      central_v += 2;
    }  else {
      central_v += 1;
    }  
  }

  return vindices;
}


std::vector<Vertex> generate_vertices_offsets(int vertex_width, int vertex_height)

{
  int n_tiles = vertex_width*vertex_height; //80
  int n_vertices = n_tiles*4;

  // 2 because abs(-1) + 1 = 2 (opengl range)
  double vertex_width_interval = 2/(double)vertex_width;
  double vertex_height_interval = 2/(double)vertex_height;

  std::vector<double> width_range = {};
  //std::vector<double> height_range = {};

  double width_counter = -1.0;
  //double height_counter = 1.0;
  width_range.push_back(width_counter);
  //height_range.push_back(height_counter);

  /// yy to do range trzeba dodac
  // -1; -0.81; -0.8; -0.61; -0.6; -0.41; -0.4; -0.21; -0.2; -0.01; 0; 0.19; 0.2; 0.39; 0.4; 0.59; 0.6; 0.79; 0.8;   1
  //  0     1      2     3     4      5      6     7     8      9   10   11   12    13   14    15    16   17    18   19 
  // fill out width range

  for(int i=0; i < vertex_width; i++)
  {
    width_counter += vertex_width_interval;
    double rounded_min = (truncf(width_counter * 100)/100) - 0.01;
    double rounded_max = (truncf(width_counter * 100)/100);
    if(rounded_min == 0.0) {rounded_min = 0;}
    if(rounded_max == 0.0) {rounded_max = 0;}

    // nie dobrze nie dobrze
    // ide spac
    if(rounded_min != 0.99){width_range.push_back(rounded_min);}
    //width_range.push_back(rounded_min);
    width_range.push_back(rounded_max);
  }  

  // for(int i=0; i<width_range.size(); i++)
  // {
  //   std::cout << width_range[i] << " " ;
  // } 
  //  std::cout << std::endl;

// manual for now
  std::vector<double> height_range = {1.0, 0.76, 0.75, 0.51, 0.5, 0.26, 
  0.25, 0.01, 0, -0.24, -0.25, -0.49, -0.5, -0.74, -0.75, -1.0};


  // // fill out height range
  // for(int i=0; i < vertex_height; i++)
  // {
  //   height_counter -= vertex_height_interval;
  //   double rounded = truncf(height_counter * 100)/100;
  //   if(rounded == 0.0)
  //   {//looks ridiculous but I want positive 0
  //     rounded = 0;
  //   }
  //   height_range.push_back(rounded);
  // }





  std::vector<Vertex> vertices = {};
  // variables for counting tile_id (starting from 1)
  int VERTEX_COUNTER = 0;
  int CURRENT_TILE = 1;
  // for each height make a row 
  for(int h=0; h<height_range.size(); h++)
  {
    for(int w=0; w<width_range.size(); w++)
    {
      Vertex v;
      v.x_pos = width_range[w];
      v.y_pos = height_range[h];
      v.z_pos = 0.0;

      // colors
      v.r_col = (double) rand()/RAND_MAX;
      v.g_col = (double) rand()/RAND_MAX;
      v.b_col = (double) rand()/RAND_MAX;
      v.a_col = 1.0f;

      // tile type
      v.tile_type = 10;

      float tex_coord_x = 0;
      float tex_coord_y = 0;
      if(w%2 == 1){tex_coord_x = 0.249;};
      if(h%2 == 1){tex_coord_y = 1;};

      v.tex_coord_x = tex_coord_x;
      v.tex_coord_y = tex_coord_y;

      // assign tile_id
      //v.tile_id = CURRENT_TILE;
      v.vertex_id = VERTEX_COUNTER;
      vertices.push_back(v);

      VERTEX_COUNTER += 1;
      // CURRENT_TILE = std::round(VERTEX_COUNTER/4) + 1;
    } 
  }

  // for(int v=0; v< vertices.size(); v++)
  // {
  //   std::cout << vertices[v].x_pos << " " << vertices[v].y_pos << std::endl;
  // }
  return vertices;
}


std::vector<Quad> generate_quad_list(int vertex_width, int vertex_height)
{

  int vertex_width_size = vertex_width*2; //20
  int vertex_height_size = vertex_height*2; //16
  int n_vertices = vertex_width_size*vertex_height_size; //320

  std::vector<Quad> quads = {};
  int n_quads = vertex_width*vertex_height; 
  int offset = 0;
  for(int i = 0; i < n_quads; i++)
  {
    Quad t;
    t.quad_id = i+1;
    int j = i + offset;

    t.top_left = (j*2);
    t.top_right = (j*2)+1;
    t.bottom_left = ((j*2)+vertex_width_size);
    t.bottom_right = (((j*2)+1)+vertex_width_size);
    quads.push_back(t);
    if(t.quad_id%vertex_width == 0){offset += vertex_width;};
    std::cout << offset << std::endl;
    // std::cout << "Tile id: " << t.tile_id  << std::endl << t.top_left << " " << t.top_right  << std::endl <<
    // t.bottom_left << " " << t.bottom_right << std::endl;
  }

  return quads;
}



std::vector<Vindex> generate_vindices_offsets(std::vector<Quad> quads)
{
  // this amount of indices I need (each tile = quad and then *2)
  std::vector<Vindex> vindices = {};
  for(int q=0; q < quads.size(); q++)
  {
    Vindex v_l;
    v_l.a = quads[q].top_left;
    v_l.b = quads[q].top_right;
    v_l.c = quads[q].bottom_left;
    vindices.push_back(v_l);

    Vindex v_r;
    v_r.a = quads[q].top_right;
    v_r.b = quads[q].bottom_right;
    v_r.c = quads[q].bottom_left;
    vindices.push_back(v_r);
  }
  return vindices;
}


