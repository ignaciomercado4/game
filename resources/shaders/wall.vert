#version 430 core

layout (location = 0) in vec3 l_vertex_position;
layout (location = 1) in vec3 l_vertex_color;
layout (location = 2) in vec3 l_vertex_normal;
layout (location = 3) in vec2 l_texture_coordinate;

uniform mat4 u_P;
uniform mat4 u_V;
uniform mat4 u_M;
uniform float u_tile_size; 

out vec3 frag_color;
out vec3 frag_normal;
out vec3 frag_pos;
out vec2 frag_tex_coord;

void main(void)
{
    vec4 world_pos4 = u_M * vec4(l_vertex_position, 1.0);
    vec3 world_pos = world_pos4.xyz;
    frag_pos = world_pos;

    frag_normal = normalize(mat3(transpose(inverse(u_M))) * l_vertex_normal);

    frag_color = l_vertex_color;

    vec3 tangent = normalize((u_M * vec4(1.0, 0.0, 0.0, 0.0)).xyz);

    float horizontal_coord = dot(world_pos, tangent);

    float vertical_coord = world_pos.y;

    frag_tex_coord = vec2(horizontal_coord, vertical_coord) / u_tile_size;

    gl_Position = u_P * u_V * world_pos4;
}
