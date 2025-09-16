#version 430 core

in vec3 frag_color;
out vec4 final_frag_color;

void main(void)
{
    final_frag_color = vec4(frag_color, 0.5f);
}