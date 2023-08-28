#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (std140) uniform CameraMatrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

uniform vec3 offset;

out vec3 fColor;


void main()
{
    fColor = aColor;
    gl_Position = projection * view * model * vec4(aPos + offset, 1.0);    
}