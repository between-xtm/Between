#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

void main()
{
    gl_Position = gl_in[0].gl_Position + vec4(gs_in[0].normal*0.05, 0.0);
    EmitVertex();
    gl_Position = gl_in[1].gl_Position + vec4(gs_in[1].normal*0.05, 0.0);
    EmitVertex();
    gl_Position = gl_in[2].gl_Position + vec4(gs_in[1].normal*0.05, 0.0);
    EmitVertex();
    EndPrimitive();
}