#ifndef TEXTURES_H
#define TEXTURES_H

namespace textures
{

  SDL_Texture *load_texture(const char *img_path, SDL_Renderer *rend)
  {
    SDL_Surface *temp_surface = IMG_Load(img_path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, temp_surface);
    SDL_FreeSurface(temp_surface);
    return tex;
  };


  struct ObjectFrame
  {
    int state_id;
    int x;
    int y;
    int w;
    int h;
  };

  struct TileFrame
  {
    int state_id;
    int x;
    int y;
    int w;
    int h;
    int solid;
  };

  struct ItemFrame
  {
    int x;
    int y;
    int w;
    int h;
    int state_id;
    int dest_offset_x;
    int dest_offset_y;
  };

  std::map<std::string, std::vector<struct ObjectFrame>> object_frames_catalog;
  std::map<std::string, std::vector<struct TileFrame>> tile_frames_catalog;
  std::map<std::string, std::vector<struct ItemFrame>> item_frames_catalog;

  struct Size
  {
    int w;
    int h;
  };

  std::map<std::string, struct Size> sizes;


  

  std::vector<struct TileFrame> read_tiles_spritesheet(const char *img_json_path)
  {
    std::ifstream json_file(img_json_path);
    std::ostringstream tmp;
    tmp << json_file.rdbuf();
    std::string s = tmp.str();

    std::regex e("\\{(.*) (.*) (.*) (.*) (.*) (.*)\\}");
    std::regex e2(": .([0-9])*");
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> a(s.begin(), s.end(), e);
    std::vector<struct TileFrame> frames = {};

    while (a != rend)
    {

      struct TileFrame f;
      std::string s(*a++);
      std::regex_token_iterator<std::string::iterator> numbers(s.begin(), s.end(), e2);
      std::vector<int> numbers_v = {};
      while (numbers != rend)
      {
        std::string number_string(*numbers++);
        std::string number_clean;
        number_clean = number_string.replace(0, 2, "");
        numbers_v.push_back(std::stoi(number_clean));
      }

      f.x = numbers_v[0];
      f.y = numbers_v[1];
      f.w = numbers_v[2];
      f.h = numbers_v[3];
      f.state_id = numbers_v[4];
      f.solid = numbers_v[5];
      frames.push_back(f);
    }
    return frames;
  }

  std::vector<struct ObjectFrame> read_object_spritesheet(const char *img_json_path)
  {
    std::ifstream json_file(img_json_path);
    std::ostringstream tmp;
    tmp << json_file.rdbuf();
    std::string s = tmp.str();

    std::regex e("\\{(.*) (.*) (.*) (.*) (.*)\\}");
    std::regex e2(": .([0-9])*");
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> a(s.begin(), s.end(), e);
    std::vector<struct ObjectFrame> frames = {};

    while (a != rend)
    {

      struct ObjectFrame f;
      std::string s(*a++);
      std::regex_token_iterator<std::string::iterator> numbers(s.begin(), s.end(), e2);
      std::vector<int> numbers_v = {};
      while (numbers != rend)
      {
        std::string number_string(*numbers++);
        std::string number_clean;
        number_clean = number_string.replace(0, 2, "");
        numbers_v.push_back(std::stoi(number_clean));
      }

      f.x = numbers_v[0];
      f.y = numbers_v[1];
      f.w = numbers_v[2];
      f.h = numbers_v[3];
      f.state_id = numbers_v[4];
      frames.push_back(f);
    }
    return frames;
  }

  std::vector<struct ItemFrame> read_item_spritesheet(const char *img_json_path)
  {
    std::ifstream json_file(img_json_path);
    std::ostringstream tmp;
    tmp << json_file.rdbuf();
    std::string s = tmp.str();

    std::regex e("\\{(.*) (.*) (.*) (.*) (.*) (.*) (.*)\\}");
    std::regex e2(": .([0-9])*");
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> a(s.begin(), s.end(), e);
    std::vector<struct ItemFrame> frames = {};

    while (a != rend)
    {

      struct ItemFrame f;
      std::string s(*a++);
      std::regex_token_iterator<std::string::iterator> numbers(s.begin(), s.end(), e2);
      std::vector<int> numbers_v = {};
      while (numbers != rend)
      {
        std::string number_string(*numbers++);
        std::string number_clean;
        number_clean = number_string.replace(0, 2, "");
        numbers_v.push_back(std::stoi(number_clean));
      }

      f.x = numbers_v[0];
      f.y = numbers_v[1];
      f.w = numbers_v[2];
      f.h = numbers_v[3];
      f.dest_offset_x = numbers_v[4];
      f.dest_offset_y = numbers_v[5];
      f.state_id = numbers_v[6];
      frames.push_back(f);
    }
    return frames;
  }

  void init()
  {
    logg::print("Init texture data read...",1);
    // this probably has to be split, its growing too large
    // EVEN A DAMN STICK HAS ITS OWN SPRITESHEET NOWADAYS HUH
    object_frames_catalog["barbarian"] = textures::read_object_spritesheet("assets/barbarian_spritesheet.json");
    sizes["barbarian"].h = 90;
    sizes["barbarian"].w = 58;

    object_frames_catalog["skeleton"] = textures::read_object_spritesheet("assets/skeleton_spritesheet.json");
    sizes["skeleton"].h = 96;
    sizes["skeleton"].w = 96;

    object_frames_catalog["ripper"] = textures::read_object_spritesheet("assets/ripper_spritesheet.json");
    sizes["ripper"].h = 96;
    sizes["ripper"].w = 96;

    object_frames_catalog["items"] = textures::read_object_spritesheet("assets/items_spritesheet.json");
    tile_frames_catalog["forest"] = textures::read_tiles_spritesheet("assets/forest_spritesheet.json");
    tile_frames_catalog["dungeon"] = textures::read_tiles_spritesheet("assets/dungeon_spritesheet.json");

    item_frames_catalog["stick"] = textures::read_item_spritesheet("assets/stick_spritesheet.json"); // stick
    logg::print("Read texture data!",1);
  }

  SDL_Rect read_tile_state_coords(std::string spritesheet_name, int state_id)
  {
    // handle door ids:
    if((state_id >= 20) && (state_id <= 29))
    {
      state_id = 20;
    };

    int index;
    for (int i = 0; i < textures::tile_frames_catalog[spritesheet_name].size(); i++)
    {
      if (textures::tile_frames_catalog[spritesheet_name][i].state_id == state_id)
      {
        index = i;
        break;
      }
    }
    SDL_Rect coords = {textures::tile_frames_catalog[spritesheet_name][index].x,
                       textures::tile_frames_catalog[spritesheet_name][index].y,
                       textures::tile_frames_catalog[spritesheet_name][index].w,
                       textures::tile_frames_catalog[spritesheet_name][index].h};
    return coords;
  };

  SDL_Rect read_object_state_coords(std::string spritesheet_name, int state_id)
  {

    int index = 999;
    for (int i = 0; i < textures::object_frames_catalog[spritesheet_name].size(); i++)
    {
      if (textures::object_frames_catalog[spritesheet_name][i].state_id == state_id)
      {
        index = i;
        break;
      }
    }
    SDL_Rect  coords;

    if(index < 999){
      coords = {textures::object_frames_catalog[spritesheet_name][index].x,
                textures::object_frames_catalog[spritesheet_name][index].y,
                textures::object_frames_catalog[spritesheet_name][index].w,
                textures::object_frames_catalog[spritesheet_name][index].h
                       };
    } else {
      logg::print("ERROR: No object_frames_catalog for spritesheetname: " + spritesheet_name, 2);
      coords = {0,0,0,0};
    }

    return coords;
  };

    std::vector<int> read_item_state_coords(std::string spritesheet_name, int state_id)
  {

    int index;
    // for(int i = 0; i < textures::item_frames_catalog[spritesheet_name].size(); i++)
    // {
    //   std::cout << textures::item_frames_catalog[spritesheet_name][i].x << std::endl;

    // }

    for (int i = 0; i < textures::item_frames_catalog[spritesheet_name].size(); i++)
    {
      if (textures::item_frames_catalog[spritesheet_name][i].state_id == state_id)
      {
        index = i;
        break;
      }
    }
    std::vector<int> coords = {textures::item_frames_catalog[spritesheet_name][index].x,
                       textures::item_frames_catalog[spritesheet_name][index].y,
                       textures::item_frames_catalog[spritesheet_name][index].w,
                       textures::item_frames_catalog[spritesheet_name][index].h,
                       textures::item_frames_catalog[spritesheet_name][index].dest_offset_x,
                       textures::item_frames_catalog[spritesheet_name][index].dest_offset_y
                       };
    return coords;
  };

  bool is_solid(std::string spritesheet_name, int state_id)
  {
    int index = 999;
    for (int i = 0; i < textures::tile_frames_catalog[spritesheet_name].size(); i++)
    {
      if (textures::tile_frames_catalog[spritesheet_name][i].state_id == state_id)
      {
        index = i;
        break;
      }
    }
    if(index < 999){
      return textures::tile_frames_catalog[spritesheet_name][index].solid;
    } else {
      return 0;
    }
  }

  std::map<std::string, SDL_Texture*> level_tex_map = {
              {"dungeon", textures::load_texture("assets/dungeon_spritesheet.png", RENDERER)},
              {"forest", textures::load_texture("assets/forest_spritesheet.png", RENDERER)}};


  SDL_Texture *items_tex = textures::load_texture("assets/items_spritesheet.png", RENDERER);
  SDL_Texture *stick_tex = textures::load_texture("assets/stick_spritesheet.png", RENDERER);

  SDL_Texture *field = textures::load_texture("field.png", RENDERER); 

};

#endif