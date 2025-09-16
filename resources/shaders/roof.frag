#version 430 core

in vec3 frag_color;
in vec3 frag_normal;
in vec3 frag_pos;
in vec2 frag_tex_coord;

out vec4 final_color;

uniform vec3 u_light_pos; 
uniform vec3 u_light_color;
uniform sampler2D u_texture; 

void main(void)
{
    vec3 base_model_color = texture(u_texture, frag_tex_coord).rgb;

    vec3 ambient = vec3(0.5f, 0.5f, 0.5f);

    vec3 norm = normalize(frag_normal);
    vec3 light_dir = normalize(u_light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * u_light_color; 

    vec3 lighting = ambient + diffuse;
    vec3 color = base_model_color * lighting;

    final_color = vec4(color, 1.0f);
}
