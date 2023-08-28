#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec2 TexCoords;
} vs_in;


uniform sampler2D texture1;



void main()
{   
    FragColor = texture(texture1, vs_in.TexCoords);
}