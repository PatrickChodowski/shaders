#ifndef TEXTURES_H
#define TEXTURES_H

namespace textures
{
  unsigned int load(unsigned int texture_id, std::string img_name, int width, int height, int n_channels)
  {
    // loads texture into CPU and later into GPU
    // use this to flip the image on read
    stbi_set_flip_vertically_on_load(true);  

    // this reads texture information 
    unsigned char *image_data = stbi_load(img_name.c_str(), &width, &height, &n_channels, 4); 

    // generate texture names (number of textures, array in which the generated texture will be stored)
    GlCall(glGenTextures(1, &texture_id)); 
    GlCall(glBindTexture(GL_TEXTURE_2D, texture_id));

    // set those parameters everytime
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));	
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

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



}


#endif
