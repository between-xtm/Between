#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out mat4 x;
out mat4 y;

uniform mat4 view;
//uniform mat4 model;
uniform mat4 projection;

void main()
{
	//gl_Position =  projection * view * vec4(aPos, 1.0);
	x = view * projection;
	y = projection * view;
	gl_Position = vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}