
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



// std::map<int, Vertex> generate_vertices(int map_vertex_width, int map_vertex_height, int tile_dim)
// {
//   int n_tiles = map_vertex_width*map_vertex_height; //80

//   std::vector<int> width_range = {};
//   int current_x_left = 0;
//   for(int i=0; i < map_vertex_width; i++)
//   {
//     width_range.push_back((current_x_left + (tile_dim*i) + (i*1) ));
//     width_range.push_back((current_x_left + (tile_dim*(i+1) + (i*1) )));
//   }  
//   // for(int i=0; i<width_range.size(); i++)
//   // {
//   //   std::cout << width_range[i] << " " ;
//   // } 
//   //  std::cout << std::endl;

//   std::vector<int> height_range = {};
//   int current_y_top = 0;
//   for(int i=0; i < map_vertex_height; i++)
//   {
//     height_range.push_back((current_y_top + (tile_dim*i) + (i*1) ));
//     height_range.push_back((current_y_top + (tile_dim*(i+1) + (i*1) )));
//   }  


//   std::map<int, Vertex> vertices = {};
//   // variables for counting tile_id (starting from 1)
//   int VERTEX_COUNTER = 0;
//   int CURRENT_TILE = 1;
//   // for each height make a row 
//   for(int h=0; h<height_range.size(); h++)
//   {
//     for(int w=0; w<width_range.size(); w++)
//     {
//       Vertex v;
//       v.x_pos = width_range[w];
//       v.y_pos = height_range[h];
//       v.z_pos = 0.0;

//       // colors
//       v.r_col = (double) rand()/RAND_MAX;
//       v.g_col = (double) rand()/RAND_MAX;
//       v.b_col = (double) rand()/RAND_MAX;
//       v.a_col = 1.0f;

//       // tile type
//       v.tile_type = 10;

//       float tex_coord_x = 0;
//       float tex_coord_y = 0;
//       if(w%2 == 1){tex_coord_x = 0.249;};
//       if(h%2 == 1){tex_coord_y = 1;};

//       v.tex_coord_x = tex_coord_x;
//       v.tex_coord_y = tex_coord_y;

//       // assign tile_id
//       //v.tile_id = CURRENT_TILE;
//       v.vertex_id = VERTEX_COUNTER;
//       //vertices.push_back(v);

//       vertices.insert({VERTEX_COUNTER, v});

//       VERTEX_COUNTER += 1;
//       // CURRENT_TILE = std::round(VERTEX_COUNTER/4) + 1;
//     } 
//   }

//   // for(int v=0; v< vertices.size(); v++)
//   // {
//   //   std::cout << "VERTEX: " << vertices[v].vertex_id << " - " << vertices[v].x_pos << " " << vertices[v].y_pos << std::endl;
//   // }
//   return vertices;
// }

// std::vector<Quad> generate_quad_list(int map_vertex_width, int map_vertex_height)
// {

//   int vertex_width_size = map_vertex_width*2; 
//   int vertex_height_size = map_vertex_height*2; 

//   std::vector<Quad> quads = {};
//   int n_quads = map_vertex_width*map_vertex_height; 
//   int offset = 0;
//   for(int i = 0; i < n_quads; i++)
//   {
//     Quad t;
//     t.quad_id = i+1;
//     int j = i + offset;

//     t.top_left = (j*2);
//     t.top_right = (j*2)+1;
//     t.bottom_left = ((j*2)+vertex_width_size);
//     t.bottom_right = (((j*2)+1)+vertex_width_size);
//     quads.push_back(t);
//     if(t.quad_id%map_vertex_width == 0){offset += map_vertex_height;};
//   }

//   return quads;
// }



// std::vector<Vindex> generate_vindices(std::vector<Quad> quads)
// {
//   // this amount of indices I need (each tile = quad and then *2)
//   std::vector<Vindex> vindices = {};
//   for(int q=0; q < quads.size(); q++)
//   {
//     Vindex v_l;
//     v_l.a = quads[q].top_left;
//     v_l.b = quads[q].top_right;
//     v_l.c = quads[q].bottom_left;
//     vindices.push_back(v_l);

//     Vindex v_r;
//     v_r.a = quads[q].top_right;
//     v_r.b = quads[q].bottom_right;
//     v_r.c = quads[q].bottom_left;
//     vindices.push_back(v_r);
//   }

//   // for(int v=0; v< vindices.size(); v++)
//   // {
//   //   std::cout << "VINDEX: " << vindices[v].a << " " << vindices[v].b << " " << vindices[v].c << std::endl;
//   // }
//   return vindices;
// }


glm::mat4 generate_mvp()
{
  glm::mat4 proj = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  glm::mat4 mvp = proj*view*model;
  return proj;
}
