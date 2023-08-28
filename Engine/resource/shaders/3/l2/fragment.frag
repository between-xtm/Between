#version 330 core
out vec4 FragColor;

uniform float ugreenValue;

void main()
{
    FragColor = vec4(0.0f, ugreenValue, 0.0f, 1.0f);
}