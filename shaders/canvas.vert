#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_tex_coord;

void main(void) {
    gl_Position = vec4(in_position.x, in_position.y, 0.0, 1.0);
}
