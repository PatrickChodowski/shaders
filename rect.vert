#version 330 core
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;

// We output the ex_Color variable to the next shader in the chain
out vec3 out_color;

void main(void) {
    // Since we are using flat lines, our input only had two points: x and y.
    // Set the Z coordinate to 0 and W coordinate to 1
    gl_Position = vec4(in_position.x, in_position.y, 0.0, 1.0);
    // We're simply passing the color through unmodified
    out_color = in_color;
}
