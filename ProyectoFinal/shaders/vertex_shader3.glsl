#version 410 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;

// out vec3 fragColor;
//out vec3 height;
uniform float grad_length;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // fragColor = color;
    //height = vec3(0.0,position.y,0.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
}