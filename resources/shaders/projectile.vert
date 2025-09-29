#version 430 core

layout (location = 0) in vec3 l_vertex_position;
layout (location = 3) in vec2 l_texture_coordinate;

uniform mat4 u_P;
uniform mat4 u_V;
uniform mat4 u_M;

out vec3 frag_pos;
out vec2 frag_tex_coord;

void main(void)
{
    vec4 world_pos = u_M * vec4(l_vertex_position, 1.0f);
    frag_pos = world_pos.xyz;

    frag_tex_coord = l_texture_coordinate; 

    gl_Position = u_P * u_V * world_pos;
}
