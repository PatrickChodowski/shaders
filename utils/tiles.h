#ifndef TILES_H
#define TILES_H

// Everything related to rendering tiles

namespace tiles
{
  struct V_Index
  {
    int i_a;
    int i_b;
    int i_c;
  };

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

    // vindices
    struct V_Index left_vi;
    // a b
    // c


    struct V_Index right_vi;
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
  int offset = 0;

  for(int i = 0; i < level_tile_map.size(); i++)
  {
    int j = i + offset;
    level_tile_map[i].a = (j*2);
    level_tile_map[i].b = (j*2)+1;
    level_tile_map[i].c = ((j*2)+vertex_width_size);
    level_tile_map[i].d = (((j*2)+1)+vertex_width_size);

     // create vindices 
     level_tile_map[i].left_vi.i_a = level_tile_map[i].a;
     level_tile_map[i].left_vi.i_b = level_tile_map[i].b;
     level_tile_map[i].left_vi.i_c = level_tile_map[i].c;

     level_tile_map[i].right_vi.i_a = level_tile_map[i].b;
     level_tile_map[i].right_vi.i_b = level_tile_map[i].d;
     level_tile_map[i].right_vi.i_c = level_tile_map[i].c;


    if(level_tile_map[i].id%map_vertex_width == 0){offset += map_vertex_height;};
  }



  //for(int t=0; t<level_tile_map.size(); t++)
  for(int t=0; t<10; t++)
  {
    std::cout << "Tile: " << level_tile_map[t].id << " - "<< level_tile_map[t].type << std::endl << 
    level_tile_map[t].x  << "," << level_tile_map[t].y << std::endl <<
    "Vertices:" << std::endl <<
    level_tile_map[t].a << " " << level_tile_map[t].b << std::endl <<
    level_tile_map[t].c << " " << level_tile_map[t].d << std::endl <<
    "Vindices:" << std::endl <<
    level_tile_map[t].left_vi.i_a << " " << level_tile_map[t].left_vi.i_b << " " << level_tile_map[t].left_vi.i_c << std::endl <<
    level_tile_map[t].right_vi.i_a << " " << level_tile_map[t].right_vi.i_b << " " << level_tile_map[t].right_vi.i_c << std::endl;
  }


  
  return level_tile_map;


}






}


#endif
