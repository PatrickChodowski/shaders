#ifndef BUFFER_H
#define BUFFER_H

namespace buffer
{
  unsigned int VBO, VAO, EBO;
  void init(std::map<int, Vertex> vertices_tilemap, std::vector<Vindex> vindices_tilemap)
  {

    // generate vertices array out of vector of Vertices:
    int n_vertices = vertices_tilemap.size();
    int vertices_array_size = COUNT_VERTEX_ATTRIBUTES*n_vertices;
    float vertices_array[vertices_array_size];
 
    for(int v=0; v<n_vertices; v++)
    {
      int start_position = v*COUNT_VERTEX_ATTRIBUTES;
      vertices_array[start_position] = vertices_tilemap[v].x_pos;
      vertices_array[(start_position+1)] = vertices_tilemap[v].y_pos;
      vertices_array[(start_position+2)] = vertices_tilemap[v].z_pos;

      vertices_array[(start_position+3)] = vertices_tilemap[v].r_col;
      vertices_array[(start_position+4)] = vertices_tilemap[v].g_col;
      vertices_array[(start_position+5)] = vertices_tilemap[v].b_col;
      vertices_array[(start_position+6)] = vertices_tilemap[v].a_col;

      vertices_array[(start_position+7)] = vertices_tilemap[v].tile_type;

      vertices_array[(start_position+8)] = vertices_tilemap[v].tex_coord_x;
      vertices_array[(start_position+9)] = vertices_tilemap[v].tex_coord_y;

      // std::cout << "VERTEX " << v << ": " << vertices_tilemap[v].tex_coord_x << " " << 
      // vertices_tilemap[v].tex_coord_y << std::endl;

    }

    // generate indices array out of vector of Indices:
    int n_vindices = vindices_tilemap.size();
    int vindices_array_size = 3*n_vindices; // its always 3 as it is a triangle
    unsigned int vindices_array[vindices_array_size];
    for(int i=0; i<n_vindices; i++)
    {
      int start_position = i*3;
      vindices_array[start_position] = vindices_tilemap[i].a;
      vindices_array[(start_position+1)] = vindices_tilemap[i].b;
      vindices_array[(start_position+2)] = vindices_tilemap[i].c;

      // std::cout << "VINDEX " << i << ": " << vindices_tilemap[i].a << " " << 
      // vindices_tilemap[i].b << " " << vindices_tilemap[i].c << " " << 
      // std::endl;
    }
  // vertex is not position, vertex can have much more than the position - so we pass a lot of data in vertices
  // then we generate buffer, bind it and add data ( vertices data)
  // they are all attributes

      // buffers are based in GPU (vram)
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);

      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_array), vertices_array, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vindices_array), vindices_array, GL_STATIC_DRAW);

    // new version:
    // position attribute:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // enable this attribute at the end

    // color attribute:
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // enable this attribute at the end

    // tile_type attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2); // enable this attribute at the end

    // in texture coordinates attribute
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3); // enable this attribute at the end



    // position attribute
    /*
    glVertexAttribPointer(
       index - index of the generic vertex attribute, 
       size - count of elements per vertex,
       type - type of element, for example float
       normalize -  true/false, not needed for float
       stride - byte offset, amount of bytes between each vertex (size of each vertex)
       pointer - offset of attribute within vertex
       )
    */
  }

  // void init_from_level_map(std::vector<tiles::Tile> level_map)
  // {


  //   // generate vertices array out of vector of Vertices:
  //   int n_vertices = level_map.size();
  //   int vertices_array_size = COUNT_VERTEX_ATTRIBUTES*n_vertices;
  //   float vertices_array[vertices_array_size];
 
  //   for(int v=0; v<n_vertices; v++)
  //   {
  //     int start_position = v*COUNT_VERTEX_ATTRIBUTES;
  //     vertices_array[start_position] = vertices_tilemap[v].x_pos;
  //     vertices_array[(start_position+1)] = vertices_tilemap[v].y_pos;
  //     vertices_array[(start_position+2)] = vertices_tilemap[v].z_pos;

  //     vertices_array[(start_position+3)] = vertices_tilemap[v].r_col;
  //     vertices_array[(start_position+4)] = vertices_tilemap[v].g_col;
  //     vertices_array[(start_position+5)] = vertices_tilemap[v].b_col;
  //     vertices_array[(start_position+6)] = vertices_tilemap[v].a_col;

  //     vertices_array[(start_position+7)] = vertices_tilemap[v].tile_type;

  //     vertices_array[(start_position+8)] = vertices_tilemap[v].tex_coord_x;
  //     vertices_array[(start_position+9)] = vertices_tilemap[v].tex_coord_y;

  //     // std::cout << "VERTEX " << v << ": " << vertices_tilemap[v].tex_coord_x << " " << 
  //     // vertices_tilemap[v].tex_coord_y << std::endl;

  //   }



  // }




  void drop()
  {
    glDeleteVertexArrays(1, &buffer::VAO);
    glDeleteBuffers(1, &buffer::VBO);
    glDeleteBuffers(1, &buffer::EBO);
  }

}



#endif
