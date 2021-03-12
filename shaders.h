#ifndef SHADERS_H
#define SHADERS_H

namespace shaders 
{
  std::map<std::string, int> variables;

  GPU_Image *img;
  int v, f, p;

  // Shader Block =  Container  for the built-in shader attribute and uniform locations (indices)
  // position_loc, texcoord_loc, color_loc, modelCiewProjection_loc
  GPU_ShaderBlock block;

  void init(std::string shader_id)
  {
      std::string v_str = shader_id+".vert";
      std::string f_str = shader_id+".frag";

    // GPU_LoadShader(Shader_type (GPU_ShaderEnum), filename) 
    // loads shader source from file, compiles it and returns shader object

    //GPU_ShaderEnum: 
    // 0: Vertex  (vertices - wierzcholek)
    // The vertex shader is used to transform the attributes of vertices (points of triangle)
    // It allows the original objects to be distorted or reshaped in any manner.
    // Changes shape of the object
    // Output goes to fragment shader

    // 1: Fragment (pixel shader)
    // Changes appearance of the object
    v = GPU_LoadShader(GPU_VERTEX_SHADER, v_str.c_str());

		if (!v)
    {
			std::cout << "Failed to load vertex shader: " << GPU_GetShaderMessage() << "\n";
    }

    f = GPU_LoadShader(GPU_FRAGMENT_SHADER, f_str.c_str());

    
		if (!f)
    {
			std::cout << "Failed to load fragment shader: " << GPU_GetShaderMessage() << "\n";
    }
    // Creates and links a shader program from given shader objects
    p = GPU_LinkShaders(v, f);

    
		if (!p) 
    {
			std::cout << "Failed to link shader program: " << GPU_GetShaderMessage() << "\n";
		}

    // loads in shader program(p) position_name, texcoord name, color_name, and ModelViewProjectionMatrixName
    block = GPU_LoadShaderBlock(p, 
                              "gpu_Vertex", //position name 
                              "gpu_TexCoord",  // texcoord name
                              NULL,  // color name
                              "gpu_ModelViewProjectionMatrix");


  }




  void add_variable(std::string idV) 
  {
    int location = GPU_GetUniformLocation(p, idV.c_str());
    std::cout << "location of " << idV <<  " is " << location << std::endl;
    variables.insert(std::make_pair(idV, location));
  };


  int get_var(std::string idV) 
  {

    for (auto it = variables.begin(); it != variables.end(); ++it)
    {
      if (it->first == idV)
          return it->second;
    }
    return (int)(-1);
  };

  void add_img(std::string path) 
  {
    img = GPU_LoadImage(path.c_str());
    GPU_SetSnapMode(img, GPU_SNAP_NONE);
    GPU_SetWrapMode(img, GPU_WRAP_REPEAT, GPU_WRAP_REPEAT);
  };

  void set_img_shader(std::string texture_var) 
  {
	    GPU_SetShaderImage(img, get_var(texture_var), p);
  };


  void activate() 
  {
	  GPU_ActivateShaderProgram(p, &block);
  };


}

#endif
