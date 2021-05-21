#ifndef TEXTURES_H
#define TEXTURES_H

namespace textures
{
  struct tile_coords
  {
    int x;
    int y;
    int w;
    int h;
    int x_end;


    float norm_x_start;
    float norm_x_end;
  };

  struct TileFrame
  {
    int type;
    int x;
    int y;
    int w;
    int h;
    int solid;
    int x_end;
    float texture_id;

    float norm_x_start;
    float norm_x_end;
  };


    struct ObjectFrame
  {
    int state_id;
    int x;
    int y;
    int w;
    int h;
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
  std::map<std::string, std::map<int, struct TileFrame>> tile_frames_catalog;
  std::map<std::string, std::vector<struct ItemFrame>> item_frames_catalog;

  struct Size
  {
    int w;
    int h;
  };

  std::map<std::string, struct Size> sizes;



  unsigned int load(unsigned int texture_id, std::string img_name, int width, int height, int n_channels)
  {
    // loads texture into CPU and later into GPU
    // use this to flip the image on read
    // I might have reversed the vertices instead by accident ->
    stbi_set_flip_vertically_on_load(false);  

    // this reads texture information 
    unsigned char *image_data = stbi_load(img_name.c_str(), &width, &height, &n_channels, 4); 

    // generate texture names (number of textures, array in which the generated texture will be stored)
    GlCall(glGenTextures(1, &texture_id)); 
    GlCall(glBindTexture(GL_TEXTURE_2D, texture_id));

    // set those parameters everytime
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));	
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    // specify 2 dimmensional texture image
    GlCall((glTexImage2D(GL_TEXTURE_2D, //target 
                          0, //level, 0 is base image
                          GL_RGBA, //internalformat
                          width,
                          height,  
                          0,  // border
                          GL_RGBA,  // format
                          GL_UNSIGNED_BYTE,  // type
                          image_data))); // data

    //  bind a named texture to a texturing target
    GlCall(glBindTexture(GL_TEXTURE_2D, 0));
    stbi_image_free(image_data);

    return texture_id;
  };


  void drop(unsigned int texture_id)
  {
    GlCall(glDeleteTextures(1, &texture_id));
  };

  void unbind()
  {
    GlCall(glBindTexture(GL_TEXTURE_2D, 0));
  };

  void bind(unsigned int texture_id, unsigned int slot)
  {
    GlCall(glActiveTexture(GL_TEXTURE0 + slot));
    GlCall(glBindTexture(GL_TEXTURE_2D, texture_id));
  };



  std::map<int, struct TileFrame> read_tiles_spritesheet(const char *img_json_path)
  {
    std::ifstream json_file(img_json_path);
    std::ostringstream tmp;
    tmp << json_file.rdbuf();
    std::string s = tmp.str();

    std::regex e("\\{(.*) (.*) (.*) (.*) (.*) (.*) (.*) (.*)\\}");
    std::regex e2(": .([0-9])*");
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> a(s.begin(), s.end(), e);
    std::map<int, struct TileFrame> frames;

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
      f.type = numbers_v[4];
      f.solid = numbers_v[5];
      f.x_end = numbers_v[6];
      f.texture_id = (float)numbers_v[7];

      f.norm_x_start =  (float)f.x/196.0;
      f.norm_x_end =  (float)f.x_end/196.0;
      

      frames.insert({f.type, f});
    }
    return frames;
  }





  void init()
  {
    tile_frames_catalog["dungeon"] = textures::read_tiles_spritesheet("assets/dungeon_spritesheet.json");
    tile_frames_catalog["redripper"] = textures::read_tiles_spritesheet("assets/redripper_spritesheet.json");
  }



  tile_coords read_tile_state_coords(std::string spritesheet_name, int type)
  {
    // gets coordinates of tiles per state_id in given spritesheet

    // handle door ids:
    if((type >= 20) && (type <= 29))
    {
      type = 20;
    };

    int index;
    for (int i = 0; i < textures::tile_frames_catalog[spritesheet_name].size(); i++)
    {
      if (textures::tile_frames_catalog[spritesheet_name][i].type == type)
      {
        index = i;
        break;
      }
    }
    tile_coords coords;
    coords.x = textures::tile_frames_catalog[spritesheet_name][index].x;
    coords.y = textures::tile_frames_catalog[spritesheet_name][index].y;
    coords.w = textures::tile_frames_catalog[spritesheet_name][index].w;
    coords.h = textures::tile_frames_catalog[spritesheet_name][index].h;
    return coords;
  };



}


#endif
