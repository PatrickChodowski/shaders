#version 330 core

in vec3 out_color;
in vec2 TexCoord;

out vec4 frag_color;

uniform vec2 resolution;
uniform sampler2D texture1;

void main()
{
    vec4 col = texture(texture1, TexCoord);
    frag_color = col;
}
