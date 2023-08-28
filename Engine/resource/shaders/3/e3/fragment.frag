#version 330 core

out vec4 FragColor;
in vec4 v4Pos;

void main()
{
    FragColor = v4Pos;
}