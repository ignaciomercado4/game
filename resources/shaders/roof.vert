#version 430 core

layout (location = 0) in vec3 l_vertex_position;
layout (location = 1) in vec3 l_vertex_color;
layout (location = 2) in vec3 l_vertex_normal;
layout (location = 3) in vec2 l_texture_coordinate;

uniform mat4 u_P;
uniform mat4 u_V;
uniform mat4 u_M;

out vec3 frag_color;
out vec3 frag_normal;
out vec3 frag_pos;
out vec2 frag_tex_coord;

void main(void)
{
    vec4 world_pos = u_M * vec4(l_vertex_position, 1.0f);
    frag_pos = world_pos.xyz;

    frag_normal = normalize(mat3(transpose(inverse(u_M))) * l_vertex_normal);

    frag_color = l_vertex_color;

    frag_tex_coord = l_texture_coordinate; // Hack of all hacks.

    gl_Position = u_P * u_V * world_pos;
}
