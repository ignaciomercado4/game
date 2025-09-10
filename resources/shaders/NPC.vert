#version 430 core

layout (location = 0) in vec3 l_vertex_position;
layout (location = 3) in vec2 l_vertex_uv;

uniform mat4 u_P;
uniform mat4 u_V;
uniform mat4 u_M;

out vec2 frag_uv;

void main(void)
{
    vec4 world_pos = u_M * vec4(l_vertex_position, 1.0f);
    gl_Position = u_P * u_V * world_pos;

    frag_uv = l_vertex_uv;
}
