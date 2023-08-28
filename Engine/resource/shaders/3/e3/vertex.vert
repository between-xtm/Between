#version 330 core
layout(location = 0) in vec3 aPos;

out vec4 v4Pos;
void main()
{
    gl_Position = vec4(aPos, 1.0f);
    v4Pos = gl_Position;
}