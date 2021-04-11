
// it receives only from vertex shader I suppose

varying vec4 color;
varying vec2 texCoord;
varying vec3 vertex;
uniform sampler2D tex0;

// Main function must set the gl_FragColor
// rgba takes value between 0 and 1


uniform vec2 resolution;
uniform vec2 offset;

void main() 
{
    vec2 q = texCoord;
    vec3 col = texture2D(tex0, q).xyz;
    vec2 coord = vertex.xy/resolution;
    //vec2 offset = vec2(0.5, 0.5);
    float dist = distance(coord, offset);

    //vec4 color =  vec4(coord.x, 0.0, 0.0, 1.0);
    //vec4 color =  vec4(0.5, 0.0, 0.0, (1.0-dist));
    vec4 color =  vec4(0.0, 0.0, 0.0, 0.0);

    //vec4 color  = vec4(col, pow(1.0-dist, 5.0) );

    gl_FragColor = color;
}	


// mmoze tu :D
// https://codeboxsystems.com/tutorials/en/intro-opengl-shaders-glsl-shaders-fragments/