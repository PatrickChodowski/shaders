
#ifndef WORLD_H
#define WORLD_H

namespace world
{
  struct Tile
  {
    int x;
    int y;
    int state_id;
    bool solid;
  };

  struct HeroStep
  {
    int p_x;
    int p_y;
    int x;
    int y;
  };

  struct Door
  {
    int id;
    std::string destination_level_name;
    int destination_door_id;

    int start_x; //relative to the door position
    int start_y; //relative to the door position
  };

  struct Level
  {
    std::string name;
    int id;
    std::vector<struct Door> doors = {};
    std::string spritesheet_name;
  };

  struct world::HeroStep hero_step;
  std::vector<struct Tile> TILE_MAP = {};
  std::vector<struct Tile> map_blockades = {};
  std::vector<struct Tile> doors = {};
  std::string CURRENT_LEVEL_NAME = "Dungeon lvl1";
  std::vector<struct Level> levels = {};
  std::vector<int> session_visited_levels = {};

  std::string get_spritesheet_of_level(std::string level_name)
  {
    std::string spritesheet_name;
    for (int l = 0; l < world::levels.size(); l++)
    {
      if (world::levels[l].name == level_name)
      {
        spritesheet_name = world::levels[l].spritesheet_name;
        break;
      }
    }
    return spritesheet_name;
  }

  void init_lvl(std::string lvl_name)
  {
    logg::print("World: init_lvl: "+lvl_name, 1);
    std::string file_path = "maps/" + lvl_name;
    std::ifstream in_file;
    in_file.open(file_path.c_str());
    if (in_file.is_open())
    {
      for (int r = 0; r < VECTOR_HEIGHT; r++)
      {
        for (int c = 0; c < VECTOR_WIDTH; c++)
        {
          struct Tile tile;
          tile.x = c * TILE_DIM;
          tile.y = r * TILE_DIM;
          in_file >> tile.state_id;
          std::string spritesheet_name = get_spritesheet_of_level(CURRENT_LEVEL_NAME);
          tile.solid = textures::is_solid(spritesheet_name, tile.state_id);
          TILE_MAP.push_back(tile);
        };
      };
      in_file.close();
    };
    logg::print("World: init_lvl: "+lvl_name + " finished!", 1);
  };

  int get_id_of_level(std::string level_name)
  {
    int level_id;
    for (int l = 0; l < world::levels.size(); l++)
    {
      if (world::levels[l].name == level_name)
      {
        level_id = world::levels[l].id;
        break;
      }
    }
    return level_id;
  }

  void init(std::string lvl_name)
  {
    logg::print("Initializing world: " + lvl_name + "...", 1);
    world::CURRENT_LEVEL_NAME = lvl_name;
    int level_id = get_id_of_level(world::CURRENT_LEVEL_NAME);

    // get id of level
    world::session_visited_levels.push_back(level_id);
    // add level to visited ones during the session
    ecs::remove_vector_duplicates(world::session_visited_levels);

    init_lvl(lvl_name);

    world::map_blockades.clear();
    for (int t = 0; t < world::TILE_MAP.size(); t++)
    {
      if (world::TILE_MAP[t].solid)
      {
        world::map_blockades.push_back(world::TILE_MAP[t]);
      };
    };

    world::doors.clear();
    for (int t = 0; t < world::TILE_MAP.size(); t++)
    {
      if (world::TILE_MAP[t].state_id >= 20 && world::TILE_MAP[t].state_id <= 29)
      {
        world::doors.push_back(world::TILE_MAP[t]);
      };
    };
    logg::print("World initialized", 1);
  };

  // draw map dynamically
  void render()
  {
    for (int t = 0; t < TILE_MAP.size(); t++)
    {
      SDL_Rect tile;
      std::string spritesheet_name = get_spritesheet_of_level(CURRENT_LEVEL_NAME);
      SDL_Rect src_rect = textures::read_tile_state_coords(spritesheet_name, TILE_MAP[t].state_id);
      tile = {TILE_MAP[t].x, TILE_MAP[t].y, TILE_DIM, TILE_DIM};
      SDL_RenderCopy(RENDERER, textures::level_tex_map[spritesheet_name], &src_rect, &tile);
    };
  };

  void destroy_world()
  {
    SDL_DestroyTexture(textures::level_tex_map["dungeon"]);
    SDL_DestroyTexture(textures::level_tex_map["forest"]);
    SDL_DestroyTexture(textures::items_tex);
    SDL_DestroyTexture(textures::stick_tex);
  };

  void init_world_map()
  {

    struct Door door1_1;
    door1_1.id = 21;
    door1_1.destination_level_name = "Forest lvl1";
    door1_1.destination_door_id = 21;
    door1_1.start_x = -TILE_DIM;
    door1_1.start_y = 0;

    struct Level lvl1;
    lvl1.name = "Dungeon lvl1";
    lvl1.id = 1;
    lvl1.doors.push_back(door1_1);
    lvl1.spritesheet_name = "dungeon";

    struct Door door2_1;
    door2_1.id = 21;
    door2_1.destination_level_name = "Dungeon lvl1";
    door2_1.destination_door_id = 21;
    door2_1.start_x = TILE_DIM * 1.5;
    door2_1.start_y = 0;

    struct Level lvl2;
    lvl2.name = "Forest lvl1";
    lvl2.id = 2;
    lvl2.doors.push_back(door2_1);
    lvl2.spritesheet_name = "forest";

    world::levels.push_back(lvl1);
    world::levels.push_back(lvl2);
  };

  // find destination level name
  struct Door get_dest_level(std::string level, int door_id)
  {
    struct Door dest_door;
    if (world::levels.size() > 0)
    {
      for (int i = 0; i < world::levels.size(); i++)
      {
        if (world::levels[i].name == level)
        {
          if (world::levels[i].doors.size() > 0)
          {
            for (int d = 0; d < world::levels[i].doors.size(); d++)
            {
              if (world::levels[i].doors[d].id == door_id)
              {
                dest_door = world::levels[i].doors[d];
                break;
              }
            }
          }
        }
      }
      return dest_door;
    }
    else
    {
      return dest_door;
    }
  };

  struct world::Tile get_door_tile(int door_id)
  {
    struct world::Tile door_tile;
    logg::print("doors size: " + std::to_string(world::doors.size()), 1);

    if (world::doors.size() > 0)
    {
      for (int d = 0; d < world::doors.size(); d++)
      {
        if (doors[d].state_id == door_id)
        {
          door_tile = doors[d];
          return doors[d];
          break;
        }
      };
    }
    else
    {
      return door_tile;
    }
    return door_tile;
  }

  void clear()
  {
    logg::print("Clearing world...",1);
    world::map_blockades.clear();
    world::doors.clear();
    world::TILE_MAP.clear();
    logg::print("World cleared",1);
  }

};

#endif