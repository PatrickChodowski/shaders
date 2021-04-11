#version 330 core

in vec3 out_color;
in vec2 TexCoord;

out vec4 frag_color;

uniform vec2 LightCoord;
uniform sampler2D texture1;

void main()
{
    float dupa = 1/(gl_FragCoord.x - LightCoord.x);
    vec4 frag_color0 = texture(texture1, TexCoord);
    frag_color0[3] = dupa;
    frag_color = frag_color0;
}
