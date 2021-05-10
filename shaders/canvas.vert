#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

out vec4 out_color;

void main(void) {
    gl_Position = vec4(in_position.x, in_position.y, in_position.z, 1.0);
    out_color = vec4(in_color);
}
