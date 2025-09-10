#version 430 core

in vec2 frag_uv;

out vec4 final_color;

uniform sampler2D u_texture;

void main(void)
{
    final_color = texture(u_texture, frag_uv);
}
