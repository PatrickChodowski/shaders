#version 460 core

in vec4 out_color;
in vec2 out_tex_coord;
in float out_texture_id;
out vec4 frag_color;

uniform vec2 LightCoord;
uniform sampler2D textures[2];

void main()
{   
    int texture_index = int(out_texture_id);
    float bug  = 0.0;
    float dist = distance(gl_FragCoord.xy, LightCoord.xy)/120;
    vec4 col = texture(textures[texture_index], out_tex_coord);
    frag_color = mix(col, vec4(0.0, 0.0, 0.0, 1.0), dist);
}
