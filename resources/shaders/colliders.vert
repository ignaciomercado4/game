#version 430 core

layout (location = 0) in vec3 l_vertex_pos;

uniform mat4 u_M;
uniform mat4 u_V;
uniform mat4 u_P;

out vec3 frag_color;

void main(void)
{
    gl_Position = u_P * u_V * u_M * vec4(l_vertex_pos, 1.0f);
    frag_color = vec3(1.0f, 0.0f, 0.0f);
}