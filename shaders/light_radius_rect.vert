#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_tex_coord;

out vec3 out_color;
out vec2 TexCoord;

void main(void) {
    // Since we are using flat lines, our input only had two points: x and y.
    // Set the Z coordinate to 0 and W coordinate to 1
    gl_Position = vec4(in_position.x, in_position.y, 0.0, 1.0);
    // We're simply passing the color through unmodified
    out_color = in_color;
    TexCoord = in_tex_coord;
}
