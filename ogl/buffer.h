#ifndef BUFFER_H
#define BUFFER_H

namespace buffer
{

  unsigned int VBO, VAO, EBO;

  void init(std::vector<quads::Quad> quads)
  {
    // generate vertices array out of tiles struct
    int n_quads = quads.size();
    //n_tiles = 3;
    int n_vertices = n_quads*4;
    int vertices_array_size = quads::COUNT_VERTEX_ATTRIBUTES*n_vertices;
    float vertices_array[vertices_array_size];


    for(int t=0; t<n_quads; t++)
    {
      int start_position = t*quads::COUNT_VERTEX_ATTRIBUTES*4;
      int cva = quads::COUNT_VERTEX_ATTRIBUTES; // 11

      vertices_array[(start_position)] = quads[t].v_a.x_pos;
      vertices_array[(start_position+1)] = quads[t].v_a.y_pos;
      vertices_array[(start_position+2)] = quads[t].v_a.z_pos;
      vertices_array[(start_position+3)] = quads[t].v_a.r_col;
      vertices_array[(start_position+4)] = quads[t].v_a.g_col;
      vertices_array[(start_position+5)] = quads[t].v_a.b_col;
      vertices_array[(start_position+6)] = quads[t].v_a.a_col;
      vertices_array[(start_position+7)] = quads[t].v_a.tile_type;
      vertices_array[(start_position+8)] = quads[t].v_a.tex_coord_x;
      vertices_array[(start_position+9)] = quads[t].v_a.tex_coord_y;
      vertices_array[(start_position+10)] = quads[t].v_a.texture_id;

      vertices_array[(start_position+cva)] = quads[t].v_b.x_pos;
      vertices_array[(start_position+(cva+1))] = quads[t].v_b.y_pos;
      vertices_array[(start_position+(cva+2))] = quads[t].v_b.z_pos;
      vertices_array[(start_position+(cva+3))] = quads[t].v_b.r_col;
      vertices_array[(start_position+(cva+4))] = quads[t].v_b.g_col;
      vertices_array[(start_position+(cva+5))] = quads[t].v_b.b_col;
      vertices_array[(start_position+(cva+6))] = quads[t].v_b.a_col;
      vertices_array[(start_position+(cva+7))] = quads[t].v_b.tile_type;
      vertices_array[(start_position+(cva+8))] = quads[t].v_b.tex_coord_x;
      vertices_array[(start_position+(cva+9))] = quads[t].v_b.tex_coord_y;
      vertices_array[(start_position+(cva+10))] = quads[t].v_b.texture_id;

      vertices_array[(start_position+(cva*2))] = quads[t].v_c.x_pos;
      vertices_array[(start_position+(cva*2) + 1)] = quads[t].v_c.y_pos;
      vertices_array[(start_position+(cva*2) + 2)] = quads[t].v_c.z_pos;
      vertices_array[(start_position+(cva*2) + 3)] = quads[t].v_c.r_col;
      vertices_array[(start_position+(cva*2) + 4)] = quads[t].v_c.g_col;
      vertices_array[(start_position+(cva*2) + 5)] = quads[t].v_c.b_col;
      vertices_array[(start_position+(cva*2) + 6)] = quads[t].v_c.a_col;
      vertices_array[(start_position+(cva*2) + 7)] = quads[t].v_c.tile_type;
      vertices_array[(start_position+(cva*2) + 8)] = quads[t].v_c.tex_coord_x;
      vertices_array[(start_position+(cva*2) + 9)] = quads[t].v_c.tex_coord_y;
      vertices_array[(start_position+(cva*2) + 10)] = quads[t].v_c.texture_id;

      vertices_array[(start_position+(cva*3))] = quads[t].v_d.x_pos;
      vertices_array[(start_position+(cva*3) + 1)] = quads[t].v_d.y_pos;
      vertices_array[(start_position+(cva*3) + 2)] = quads[t].v_d.z_pos;
      vertices_array[(start_position+(cva*3) + 3)] = quads[t].v_d.r_col;
      vertices_array[(start_position+(cva*3) + 4)] = quads[t].v_d.g_col;
      vertices_array[(start_position+(cva*3) + 5)] = quads[t].v_d.b_col;
      vertices_array[(start_position+(cva*3) + 6)] = quads[t].v_d.a_col;
      vertices_array[(start_position+(cva*3) + 7)] = quads[t].v_d.tile_type;
      vertices_array[(start_position+(cva*3) + 8)] = quads[t].v_d.tex_coord_x;
      vertices_array[(start_position+(cva*3) + 9)] = quads[t].v_d.tex_coord_y;
      vertices_array[(start_position+(cva*3) + 10)] = quads[t].v_d.texture_id;
    }
    std::cout << "Vertices array size: " << vertices_array_size << std::endl;
    std::cout << "Quads size: " << n_quads << std::endl;

    // generate indices array out of vector of Indices:
    int n_vindices = n_quads*2;
    int vindices_array_size = 3*n_vindices; // its always 3 as it is a triangle
    unsigned int vindices_array[vindices_array_size];

    for(int t=0; t<n_quads; t++)
    {
      int start_position = t*3*2;
      vindices_array[(start_position+0)] = quads[t].i_left.a;
      vindices_array[(start_position+1)] = quads[t].i_left.b;
      vindices_array[(start_position+2)] = quads[t].i_left.c;

      vindices_array[(start_position+3)] = quads[t].i_right.a;
      vindices_array[(start_position+4)] = quads[t].i_right.b;
      vindices_array[(start_position+5)] = quads[t].i_right.c;
    }
    // dont get this part now
    // GlCall(glEnable(GL_BLEND));
    // GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


  // vertex is not position, vertex can have much more than the position - so we pass a lot of data in vertices
  // then we generate buffer, bind it and add data ( vertices data)
  // they are all attributes

      // buffers are based in GPU (vram)
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);

      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      // static approach:
      // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_array), vertices_array, GL_STATIC_DRAW);

      // dynamic approach:
      glBufferData(GL_ARRAY_BUFFER, sizeof(quads::Vertex)*2000, nullptr, GL_DYNAMIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vindices_array), vindices_array, GL_STATIC_DRAW);


    // new version:
    // position attribute:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, quads::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // enable this attribute at the end

    // color attribute:
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, quads::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // enable this attribute at the end

    // tile_type attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, quads::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2); // enable this attribute at the end

    // in texture coordinates attribute
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, quads::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3); // enable this attribute at the end

    // in texture id attribute
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, quads::COUNT_VERTEX_ATTRIBUTES * sizeof(float), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(4); // enable this attribute at the end



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

  void update(std::vector<quads::Quad> quads)
  {
    int n_quads = quads.size();
    //n_tiles = 3;
    int n_vertices = n_quads*4;
    int vertices_array_size = quads::COUNT_VERTEX_ATTRIBUTES*n_vertices;
    float vertices_array[vertices_array_size];


    for(int t=0; t<n_quads; t++)
    {
      int start_position = t*quads::COUNT_VERTEX_ATTRIBUTES*4;
      int cva = quads::COUNT_VERTEX_ATTRIBUTES; // 11

      vertices_array[(start_position)] = quads[t].v_a.x_pos;
      vertices_array[(start_position+1)] = quads[t].v_a.y_pos;
      vertices_array[(start_position+2)] = quads[t].v_a.z_pos;
      vertices_array[(start_position+3)] = quads[t].v_a.r_col;
      vertices_array[(start_position+4)] = quads[t].v_a.g_col;
      vertices_array[(start_position+5)] = quads[t].v_a.b_col;
      vertices_array[(start_position+6)] = quads[t].v_a.a_col;
      vertices_array[(start_position+7)] = quads[t].v_a.tile_type;
      vertices_array[(start_position+8)] = quads[t].v_a.tex_coord_x;
      vertices_array[(start_position+9)] = quads[t].v_a.tex_coord_y;
      vertices_array[(start_position+10)] = quads[t].v_a.texture_id;

      vertices_array[(start_position+cva)] = quads[t].v_b.x_pos;
      vertices_array[(start_position+(cva+1))] = quads[t].v_b.y_pos;
      vertices_array[(start_position+(cva+2))] = quads[t].v_b.z_pos;
      vertices_array[(start_position+(cva+3))] = quads[t].v_b.r_col;
      vertices_array[(start_position+(cva+4))] = quads[t].v_b.g_col;
      vertices_array[(start_position+(cva+5))] = quads[t].v_b.b_col;
      vertices_array[(start_position+(cva+6))] = quads[t].v_b.a_col;
      vertices_array[(start_position+(cva+7))] = quads[t].v_b.tile_type;
      vertices_array[(start_position+(cva+8))] = quads[t].v_b.tex_coord_x;
      vertices_array[(start_position+(cva+9))] = quads[t].v_b.tex_coord_y;
      vertices_array[(start_position+(cva+10))] = quads[t].v_b.texture_id;

      vertices_array[(start_position+(cva*2))] = quads[t].v_c.x_pos;
      vertices_array[(start_position+(cva*2) + 1)] = quads[t].v_c.y_pos;
      vertices_array[(start_position+(cva*2) + 2)] = quads[t].v_c.z_pos;
      vertices_array[(start_position+(cva*2) + 3)] = quads[t].v_c.r_col;
      vertices_array[(start_position+(cva*2) + 4)] = quads[t].v_c.g_col;
      vertices_array[(start_position+(cva*2) + 5)] = quads[t].v_c.b_col;
      vertices_array[(start_position+(cva*2) + 6)] = quads[t].v_c.a_col;
      vertices_array[(start_position+(cva*2) + 7)] = quads[t].v_c.tile_type;
      vertices_array[(start_position+(cva*2) + 8)] = quads[t].v_c.tex_coord_x;
      vertices_array[(start_position+(cva*2) + 9)] = quads[t].v_c.tex_coord_y;
      vertices_array[(start_position+(cva*2) + 10)] = quads[t].v_c.texture_id;

      vertices_array[(start_position+(cva*3))] = quads[t].v_d.x_pos;
      vertices_array[(start_position+(cva*3) + 1)] = quads[t].v_d.y_pos;
      vertices_array[(start_position+(cva*3) + 2)] = quads[t].v_d.z_pos;
      vertices_array[(start_position+(cva*3) + 3)] = quads[t].v_d.r_col;
      vertices_array[(start_position+(cva*3) + 4)] = quads[t].v_d.g_col;
      vertices_array[(start_position+(cva*3) + 5)] = quads[t].v_d.b_col;
      vertices_array[(start_position+(cva*3) + 6)] = quads[t].v_d.a_col;
      vertices_array[(start_position+(cva*3) + 7)] = quads[t].v_d.tile_type;
      vertices_array[(start_position+(cva*3) + 8)] = quads[t].v_d.tex_coord_x;
      vertices_array[(start_position+(cva*3) + 9)] = quads[t].v_d.tex_coord_y;
      vertices_array[(start_position+(cva*3) + 10)] = quads[t].v_d.texture_id;
    }
    // std::cout << "Vertices array size: " << vertices_array_size << std::endl;
    // std::cout << "Quads size: " << n_quads << std::endl;

    // update dynamic buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // buffer, and then the offset (so maybe some of the vertices can stay the same! - interesting idea, for example keep the map always the same!)
    // buffer, offset, size of data, data)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*vertices_array_size, vertices_array);
  }





  void drop()
  {
    glDeleteVertexArrays(1, &buffer::VAO);
    glDeleteBuffers(1, &buffer::VBO);
    glDeleteBuffers(1, &buffer::EBO);
  }

}



#endif
