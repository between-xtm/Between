#version 330 core
layout (location = 0) in vec3 aPos;
uniform float umDistance;
void main()
{
    gl_Position = vec4(aPos.x+umDistance, aPos.y, aPos.z, 1.0f);
}