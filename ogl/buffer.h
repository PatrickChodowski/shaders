#ifndef BUFFER_H
#define BUFFER_H

namespace buffer
{
  unsigned int VBO, VAO, EBO;
  void init(std::vector<tiles::Tile> tiles)
  {
    // generate vertices array out of tiles struct
    int n_vertices = tiles.size()*4;
    int vertices_array_size = tiles::COUNT_VERTEX_ATTRIBUTES*tiles.size()*4;
    float vertices_array[vertices_array_size];
 
    for(int t=0; t<tiles.size(); t++)
    {
      int start_position = t*tiles::COUNT_VERTEX_ATTRIBUTES;

      vertices_array[(start_position+0)] = tiles[t].v_a.x_pos;
      vertices_array[(start_position+1)] = tiles[t].v_a.y_pos;
      vertices_array[(start_position+2)] = tiles[t].v_a.z_pos;
      vertices_array[(start_position+3)] = tiles[t].v_a.r_col;
      vertices_array[(start_position+4)] = tiles[t].v_a.g_col;
      vertices_array[(start_position+5)] = tiles[t].v_a.b_col;
      vertices_array[(start_position+6)] = tiles[t].v_a.a_col;
      vertices_array[(start_position+7)] = tiles[t].v_a.tile_type;
      vertices_array[(start_position+8)] = tiles[t].v_a.tex_coord_x;
      vertices_array[(start_position+9)] = tiles[t].v_a.tex_coord_y;

      vertices_array[(start_position+10)] = tiles[t].v_b.x_pos;
      vertices_array[(start_position+11)] = tiles[t].v_b.y_pos;
      vertices_array[(start_position+12)] = tiles[t].v_b.z_pos;
      vertices_array[(start_position+13)] = tiles[t].v_b.r_col;
      vertices_array[(start_position+14)] = tiles[t].v_b.g_col;
      vertices_array[(start_position+15)] = tiles[t].v_b.b_col;
      vertices_array[(start_position+16)] = tiles[t].v_b.a_col;
      vertices_array[(start_position+17)] = tiles[t].v_b.tile_type;
      vertices_array[(start_position+18)] = tiles[t].v_b.tex_coord_x;
      vertices_array[(start_position+19)] = tiles[t].v_b.tex_coord_y;

      vertices_array[(start_position+20)] = tiles[t].v_c.x_pos;
      vertices_array[(start_position+21)] = tiles[t].v_c.y_pos;
      vertices_array[(start_position+22)] = tiles[t].v_c.z_pos;
      vertices_array[(start_position+23)] = tiles[t].v_c.r_col;
      vertices_array[(start_position+24)] = tiles[t].v_c.g_col;
      vertices_array[(start_position+25)] = tiles[t].v_c.b_col;
      vertices_array[(start_position+26)] = tiles[t].v_c.a_col;
      vertices_array[(start_position+27)] = tiles[t].v_c.tile_type;
      vertices_array[(start_position+28)] = tiles[t].v_c.tex_coord_x;
      vertices_array[(start_position+29)] = tiles[t].v_c.tex_coord_y;

      vertices_array[(start_position+30)] = tiles[t].v_d.x_pos;
      vertices_array[(start_position+31)] = tiles[t].v_d.y_pos;
      vertices_array[(start_position+32)] = tiles[t].v_d.z_pos;
      vertices_array[(start_position+33)] = tiles[t].v_d.r_col;
      vertices_array[(start_position+34)] = tiles[t].v_d.g_col;
      vertices_array[(start_position+35)] = tiles[t].v_d.b_col;
      vertices_array[(start_position+36)] = tiles[t].v_d.a_col;
      vertices_array[(start_position+37)] = tiles[t].v_d.tile_type;
      vertices_array[(start_position+38)] = tiles[t].v_d.tex_coord_x;
      vertices_array[(start_position+39)] = tiles[t].v_d.tex_coord_y;
    }

    // generate indices array out of vector of Indices:
    int n_vindices = tiles.size()*2;
    int vindices_array_size = 3*n_vindices; // its always 3 as it is a triangle
    unsigned int vindices_array[vindices_array_size];
    for(int t=0; t<tiles.size(); t++)
    {
      int start_position = t*3;
      vindices_array[(start_position+0)] = tiles[t].i_left.a;
      vindices_array[(start_position+1)] = tiles[t].i_left.b;
      vindices_array[(start_position+2)] = tiles[t].i_left.c;

      vindices_array[(start_position+3)] = tiles[t].i_right.a;
      vindices_array[(start_position+4)] = tiles[t].i_right.b;
      vindices_array[(start_position+5)] = tiles[t].i_right.c;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, tiles::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // enable this attribute at the end

    // color attribute:
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, tiles::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // enable this attribute at the end

    // tile_type attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, tiles::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2); // enable this attribute at the end

    // in texture coordinates attribute
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, tiles::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(8 * sizeof(float)));
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

  void drop()
  {
    glDeleteVertexArrays(1, &buffer::VAO);
    glDeleteBuffers(1, &buffer::VBO);
    glDeleteBuffers(1, &buffer::EBO);
  }

}



#endif
