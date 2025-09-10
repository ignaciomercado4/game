#version 430 core

in vec3 frag_color;
out vec4 final_color;

void main(void)
{
    final_color = vec4(frag_color, 1.0f);
}