#ifndef BUFFER_H
#define BUFFER_H

namespace buffer
{

  float vertices[] = {
    // positions          // colors           // texture coords
    0.9f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f, // bottom right
    -0.9f, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f, // bottom left
    -0.9f,  0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };
  unsigned int VBO, VAO, EBO;

  void init(std::vector<Vertex> vertices_tilemap, std::vector<Vindex> vindices_tilemap)
  {

    // generate vertices array out of vector of Vertices:
    int n_vertices = vertices_tilemap.size();
    int vertices_array_size = COUNT_VERTEX_ATTRIBUTES*n_vertices;
    float vertices_array[vertices_array_size] = {};
 
    for(int v=0; v<n_vertices; v++)
    {
      int start_position = v*7;
      vertices_array[start_position] = vertices_tilemap[v].x_pos;
      vertices_array[(start_position+1)] = vertices_tilemap[v].y_pos;
      vertices_array[(start_position+2)] = vertices_tilemap[v].z_pos;

      vertices_array[(start_position+3)] = vertices_tilemap[v].r_col;
      vertices_array[(start_position+4)] = vertices_tilemap[v].g_col;
      vertices_array[(start_position+5)] = vertices_tilemap[v].b_col;
      vertices_array[(start_position+6)] = vertices_tilemap[v].a_col;
    }

    // generate indices array out of vector of Indices:
    int n_vindices = vindices_tilemap.size();
    int vindices_array_size = 3*n_vindices; // its always 3 as it is a triangle
    unsigned int vindices_array[vindices_array_size] = {};
    for(int i=0; i<n_vindices; i++)
    {
      int start_position = i*3;
      vindices_array[start_position] = vindices_tilemap[i].a;
      vindices_array[(start_position+1)] = vindices_tilemap[i].b;
      vindices_array[(start_position+2)] = vindices_tilemap[i].c;
    }




  // vertex is not position, vertex can have much more than the position - so we pass a lot of data in vertices
  // then we generate buffer, bind it and add data ( vertices data)
  // they are all attributes



      unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
      }; 

      // buffers are based in GPU (vram)
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);

      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // enable this attribute at the end
    // color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);    
  }




  void drop()
  {
    glDeleteVertexArrays(1, &buffer::VAO);
    glDeleteBuffers(1, &buffer::VBO);
    glDeleteBuffers(1, &buffer::EBO);
  }

}



#endif
