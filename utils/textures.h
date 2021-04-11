#ifndef TEXTURES_H
#define TEXTURES_H

namespace textures
{


  unsigned int load_texture(std::string img_name, int width, int height, int n_channels)
  {
    stbi_set_flip_vertically_on_load(true);  
    // this reads texture information 
    unsigned char *data = stbi_load(img_name.c_str(), &width, &height, &n_channels, 0); 
    unsigned int texture;
    glGenTextures(1, &texture);  
    glBindTexture(GL_TEXTURE_2D, texture);  

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return texture;
  }


  void render_texture()
  {
      // openGL uses x,y,z coordinates, where Z is the depth (here set to 0, as we are now using 2D only)
      // 4 points, we want rectangle!
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        0.5f, 0.5f, 0.0f 
    };  



  }

}

#endif