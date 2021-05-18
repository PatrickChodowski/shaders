#ifndef TILES_H
#define TILES_H

// Everything related to rendering tiles
// We read level from the file - it gives information about each tile
// 

namespace tiles
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

  /// not counted as VERTEX ATTRIBUTES - yet
  int tile_id;
  int vertex_id;
};

int COUNT_VERTEX_ATTRIBUTES = 10;
int VERTEX_OFFSET = 1;

// Tile will contain information about:
// - original position (x,y of top left corner)
// - type, solid, id
// - vertex ids for a,b,c,d
// - Vindices with vertex ids
// - actual vertex information



  struct Tile
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

  };



// load level is supposed to read the tiles from the map - store the information about each tile 
// and then assign vertices to each tile, and construct indices 
// then we will store information in vector of Tile structs =  level_map


std::vector<Tile> load_level(std::string lvl_name, int map_vertex_width, int map_vertex_height, int tile_dim)
{

  std::vector<Tile> level_tile_map = {};
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
          struct Tile tile;
          tile.x = c * tile_dim;
          tile.y = r * tile_dim;
          in_file >> tile.type;
          tile.id = TILE_COUNTER;
          level_tile_map.push_back(tile);
          TILE_COUNTER += 1;
        };
      } 
  }
  in_file.close();

  // assign vertices to tiles
  int vertex_width_size = map_vertex_width*2; 
  int vertex_height_size = map_vertex_height*2; 

  for(int i = 0; i < level_tile_map.size(); i++)
  {
    // add vertex ids
    int j = i * 4;
    level_tile_map[i].a = j;
    level_tile_map[i].b = j+1;
    level_tile_map[i].c = j+2;
    level_tile_map[i].d = j+3;

    // create vertex struct - A
    level_tile_map[i].v_a.vertex_id = level_tile_map[i].a;
    level_tile_map[i].v_a.tile_id = level_tile_map[i].id;
    level_tile_map[i].v_a.tile_type = level_tile_map[i].type;
    level_tile_map[i].v_a.x_pos = level_tile_map[i].x;
    level_tile_map[i].v_a.y_pos = level_tile_map[i].y;
    level_tile_map[i].v_a.z_pos = 0.0f;
    level_tile_map[i].v_a.r_col = 0.0f;
    level_tile_map[i].v_a.g_col = 0.0f;
    level_tile_map[i].v_a.b_col = 0.0f;
    level_tile_map[i].v_a.a_col = 1.0f;
    level_tile_map[i].v_a.tex_coord_x = textures::tile_frames_catalog["dungeon"][level_tile_map[i].type].norm_x_start;
    level_tile_map[i].v_a.tex_coord_y = 0.0f;

    // create vertex struct - B
    level_tile_map[i].v_b.vertex_id = level_tile_map[i].b;
    level_tile_map[i].v_b.tile_id = level_tile_map[i].id;
    level_tile_map[i].v_b.tile_type = level_tile_map[i].type;
    level_tile_map[i].v_b.x_pos = level_tile_map[i].x + tile_dim  - VERTEX_OFFSET;
    level_tile_map[i].v_b.y_pos = level_tile_map[i].y;
    level_tile_map[i].v_b.z_pos = 0.0f;
    level_tile_map[i].v_b.r_col = 0.0f;
    level_tile_map[i].v_b.g_col = 0.0f;
    level_tile_map[i].v_b.b_col = 0.0f;
    level_tile_map[i].v_b.a_col = 1.0f;
    level_tile_map[i].v_a.tex_coord_x = textures::tile_frames_catalog["dungeon"][level_tile_map[i].type].norm_x_end;
    level_tile_map[i].v_a.tex_coord_y = 0.0f;

    // create vertex struct - C
    level_tile_map[i].v_c.vertex_id = level_tile_map[i].c;
    level_tile_map[i].v_c.tile_id = level_tile_map[i].id;
    level_tile_map[i].v_c.tile_type = level_tile_map[i].type;
    level_tile_map[i].v_c.x_pos = level_tile_map[i].x;
    level_tile_map[i].v_c.y_pos = level_tile_map[i].y + tile_dim;
    level_tile_map[i].v_c.z_pos = 0.0f;
    level_tile_map[i].v_c.r_col = 0.0f;
    level_tile_map[i].v_c.g_col = 0.0f;
    level_tile_map[i].v_c.b_col = 0.0f;
    level_tile_map[i].v_c.a_col = 1.0f;
    level_tile_map[i].v_a.tex_coord_x = textures::tile_frames_catalog["dungeon"][level_tile_map[i].type].norm_x_start;
    level_tile_map[i].v_a.tex_coord_y = 1.0f;

    // create vertex struct - D
    level_tile_map[i].v_d.vertex_id = level_tile_map[i].d;
    level_tile_map[i].v_d.tile_id = level_tile_map[i].id;
    level_tile_map[i].v_d.tile_type = level_tile_map[i].type;
    level_tile_map[i].v_d.x_pos = level_tile_map[i].x + tile_dim  - VERTEX_OFFSET;
    level_tile_map[i].v_d.y_pos = level_tile_map[i].y + tile_dim;
    level_tile_map[i].v_d.z_pos = 0.0f;
    level_tile_map[i].v_d.r_col = 0.0f;
    level_tile_map[i].v_d.g_col = 0.0f;
    level_tile_map[i].v_d.b_col = 0.0f;
    level_tile_map[i].v_d.a_col = 1.0f;
    level_tile_map[i].v_a.tex_coord_x = textures::tile_frames_catalog["dungeon"][level_tile_map[i].type].norm_x_end;
    level_tile_map[i].v_a.tex_coord_y = 1.0f;

    // create vindices 
    level_tile_map[i].i_left.a = level_tile_map[i].a;
    level_tile_map[i].i_left.b = level_tile_map[i].b;
    level_tile_map[i].i_left.c = level_tile_map[i].c;

    level_tile_map[i].i_right.a = level_tile_map[i].b;
    level_tile_map[i].i_right.b = level_tile_map[i].c;
    level_tile_map[i].i_right.c = level_tile_map[i].d;

  }



  for(int t=0; t<level_tile_map.size(); t++)
  {
    std::cout << "Tile: " << level_tile_map[t].id << " - "<< level_tile_map[t].type << std::endl << 
    level_tile_map[t].x  << "," << level_tile_map[t].y << std::endl <<
    "Vertices:" << std::endl <<
    level_tile_map[t].a << " " << level_tile_map[t].b << std::endl <<
    level_tile_map[t].c << " " << level_tile_map[t].d << std::endl <<
    "Vindices:" << std::endl <<
    level_tile_map[t].i_left.a << " " << level_tile_map[t].i_left.b << " " << level_tile_map[t].i_left.c << std::endl <<
    level_tile_map[t].i_right.a << " " << level_tile_map[t].i_right.b << " " << level_tile_map[t].i_right.c << std::endl;
  }


  
  return level_tile_map;


}






}


#endif
