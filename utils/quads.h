#ifndef TILES_H
#define TILES_H

// Everything related to rendering tiles
// We read level from the file - it gives information about each tile
// 

namespace quads
{
  struct Vindex
  {  
    int a; 
    int b;
    int c;
  };




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
  double texture_id;

  /// not counted as VERTEX ATTRIBUTES - yet
  int tile_id;
  int vertex_id;
};

int COUNT_VERTEX_ATTRIBUTES = 11;
int VERTEX_OFFSET = 1;

// Tile will contain information about:
// - original position (x,y of top left corner)
// - type, solid, id
// - vertex ids for a,b,c,d
// - Vindices with vertex ids
// - actual vertex information



  struct Quad
  {
    int id;
    int x;
    int y;
    int type;
    bool solid;

    // vertex IDS:
    int a;
    int b;
    int c;
    int d;

    // a b
    // c d

    // Vertex information
    Vertex v_a;
    Vertex v_b;
    Vertex v_c;
    Vertex v_d;

    // vindices
    struct Vindex i_left;
    // a b
    // c
    struct Vindex i_right;
    //   b
    // c d

    std::string sheet_name;

  };



// load level is supposed to read the tiles from the map - store the information about each tile 
// and then assign vertices to each tile, and construct indices 
// then we will store information in vector of Tile structs =  level_map

std::vector<Quad> assign_vertices(std::vector<Quad> quads)
{
  for(int i = 0; i < quads.size(); i++)
  { 
    // add vertex ids
    int j = i * 4;
    quads[i].a = j;
    quads[i].b = j+1;
    quads[i].c = j+2;
    quads[i].d = j+3;

    // create vertex struct - A
    quads[i].v_a.vertex_id = quads[i].a;
    quads[i].v_a.tile_id = quads[i].id;
    quads[i].v_a.tile_type = quads[i].type;
    quads[i].v_a.x_pos = (float)quads[i].x;
    quads[i].v_a.y_pos = (float)quads[i].y;
    quads[i].v_a.z_pos = 0.0f;
    quads[i].v_a.r_col = 0.0f;
    quads[i].v_a.g_col = 0.0f;
    quads[i].v_a.b_col = 0.0f;
    quads[i].v_a.a_col = 1.0f;
    quads[i].v_a.tex_coord_x = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].norm_x_start;
    quads[i].v_a.tex_coord_y = 0.0f;
    quads[i].v_a.texture_id = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].texture_id;

    // create vertex struct - B
    quads[i].v_b.vertex_id = quads[i].b;
    quads[i].v_b.tile_id = quads[i].id;
    quads[i].v_b.tile_type = quads[i].type;
    quads[i].v_b.x_pos = (float)quads[i].x + (float)TILE_DIM  - (float)VERTEX_OFFSET;
    quads[i].v_b.y_pos = (float)quads[i].y;
    quads[i].v_b.z_pos = 0.0f;
    quads[i].v_b.r_col = 0.0f;
    quads[i].v_b.g_col = 0.0f;
    quads[i].v_b.b_col = 0.0f;
    quads[i].v_b.a_col = 1.0f;
    quads[i].v_b.tex_coord_x = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].norm_x_end;
    quads[i].v_b.tex_coord_y = 0.0f;
    quads[i].v_b.texture_id = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].texture_id;


    // create vertex struct - C
    quads[i].v_c.vertex_id = quads[i].c;
    quads[i].v_c.tile_id = quads[i].id;
    quads[i].v_c.tile_type = quads[i].type;
    quads[i].v_c.x_pos = (float)quads[i].x;
    quads[i].v_c.y_pos = (float)quads[i].y + (float)TILE_DIM - (float)VERTEX_OFFSET;
    quads[i].v_c.z_pos = 0.0f;
    quads[i].v_c.r_col = 0.0f;
    quads[i].v_c.g_col = 0.0f;
    quads[i].v_c.b_col = 0.0f;
    quads[i].v_c.a_col = 1.0f;
    quads[i].v_c.tex_coord_x = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].norm_x_start;
    quads[i].v_c.tex_coord_y = 1.0f;
    quads[i].v_c.texture_id = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].texture_id;


    // create vertex struct - D
    quads[i].v_d.vertex_id = quads[i].d;
    quads[i].v_d.tile_id = quads[i].id;
    quads[i].v_d.tile_type = quads[i].type;
    quads[i].v_d.x_pos = (float)quads[i].x + (float)TILE_DIM  - (float)VERTEX_OFFSET;
    quads[i].v_d.y_pos = (float)quads[i].y + (float)TILE_DIM - (float)VERTEX_OFFSET;
    quads[i].v_d.z_pos = 0.0f;
    quads[i].v_d.r_col = 0.0f;
    quads[i].v_d.g_col = 0.0f;
    quads[i].v_d.b_col = 0.0f;
    quads[i].v_d.a_col = 1.0f;
    quads[i].v_d.tex_coord_x = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].norm_x_end;
    quads[i].v_d.tex_coord_y = 1.0f;
    quads[i].v_d.texture_id = textures::tile_frames_catalog[quads[i].sheet_name][quads[i].type].texture_id;


    // create vindices 
    quads[i].i_left.a = quads[i].a;
    quads[i].i_left.b = quads[i].b;
    quads[i].i_left.c = quads[i].c;

    quads[i].i_right.a = quads[i].b;
    quads[i].i_right.b = quads[i].c;
    quads[i].i_right.c = quads[i].d;

    

  }
  return quads;
}



std::vector<Quad> load_level(std::string lvl_name, int map_vertex_width, int map_vertex_height, int tile_dim)
{
  std::vector<Quad> level_tile_map = {};
  std::string file_path = "maps/" + lvl_name;
  std::ifstream in_file;
  in_file.open(file_path.c_str());

  int n_tiles = map_vertex_width*map_vertex_height;
  int TILE_COUNTER = 1;


  // read in the tile info
  if (in_file.is_open())
  {
    for (int r = 0; r < map_vertex_height; r++)
      {
        for (int c = 0; c < map_vertex_width; c++)
        {
          struct Quad quad;
          quad.x = c * tile_dim;
          quad.y = r * tile_dim;
          in_file >> quad.type;
          quad.id = TILE_COUNTER;
          quad.sheet_name = "dungeon";
          level_tile_map.push_back(quad);
          TILE_COUNTER += 1;
        };
      } 
  }
  in_file.close();

  //std::vector<Tile> quads = assign_vertices(level_tile_map);
  
  return level_tile_map;
}

  // // to the same for other objects?
  std::vector<Quad> load_objects()
  {
    std::vector<Quad> objects = {};
    struct Quad quad;
    quad.x=300;
    quad.y=300;
    quad.id=0;
    quad.type=10;
    quad.sheet_name = "redripper";
    objects.push_back(quad);

    //std::vector<Tile> quads = assign_vertices(objects);
    return objects;
  }


  void print_out_quads(std::vector<Quad> quads)
  {
    for(int t=0; t<quads.size(); t++)
  //for(int t=0; t<2; t++)
    {
      std::cout << "Quad: " << quads[t].id << " - "<< quads[t].type << std::endl << 
      quads[t].x  << "," << quads[t].y << std::endl <<
  
      "Vertices positions:"  << std::endl <<
      quads[t].a << " " << quads[t].v_a.x_pos << "," << quads[t].v_a.y_pos << std::endl <<
      quads[t].b << " " << quads[t].v_b.x_pos << "," << quads[t].v_b.y_pos << std::endl <<
      quads[t].c << " " << quads[t].v_c.x_pos << "," << quads[t].v_c.y_pos << std::endl <<
      quads[t].d << " " << quads[t].v_d.x_pos << "," << quads[t].v_d.y_pos << std::endl <<

      "Vindices:" << std::endl <<
      quads[t].i_left.a << " " << quads[t].i_left.b << " " << quads[t].i_left.c << std::endl <<
      quads[t].i_right.a << " " << quads[t].i_right.b << " " << quads[t].i_right.c << std::endl;
    }
  }


  std::vector<Quad> init()
  {
    std::vector<Quad> level_map = load_level(TEMP_LEVEL_NAME, MAP_VERTEX_WIDTH, MAP_VERTEX_HEIGHT, TILE_DIM);
    std::vector<Quad> entities = load_objects();
    //add all quads list together
    level_map.insert( level_map.end(), entities.begin(), entities.end() );
    std::vector<Quad> quads = assign_vertices(level_map);
    // print_out_quads(quads);
    return quads;
  }



}


#endif
