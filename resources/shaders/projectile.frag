#version 430 core

in vec3 frag_pos;
in vec2 frag_tex_coord;

out vec4 final_color;

uniform sampler2D u_texture; 

void main(void)
{
    vec4 tex_color = texture(u_texture, frag_tex_coord);
    final_color = tex_color;
}
