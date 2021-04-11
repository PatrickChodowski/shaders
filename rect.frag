#version 330 core

in vec3 out_color;
in vec2 TexCoord;

out vec4 frag_color;

uniform vec2 LightCoord;
uniform vec2 resolution;
uniform sampler2D texture1;

void main()
{
    float bug  = 0.0;
    float dist = distance(gl_FragCoord.xy, LightCoord.xy)/120;
    vec4 col = texture(texture1, TexCoord);
    frag_color = mix(col, vec4(0.0, 0.0, 0.0, 1.0), dist);
}
