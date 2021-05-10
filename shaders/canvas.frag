#version 330 core
in vec4 out_color;
in vec2 out_tex_coord;
out vec4 frag_color;



uniform sampler2D texture1;

void main()
{
  //frag_color = out_color;
  frag_color = texture(texture1, out_tex_coord);
}

