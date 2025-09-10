#include "light.h"
#include "shader.h"
#include "../math/math_n.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void draw_light_source(Light self, unsigned int shader_program)
{
    use_shader(shader_program);
    Mat4 M = mat4_identity();
    M = mat4_scale(M, VEC3(0.2f, 0.2f, 0.2f));
    M = mat4_translate(M, self.position);
    set_mat4_uniform(shader_program, M, "u_M");
    set_vec3_uniform(shader_program, self.color, "u_light_color");
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void draw_lights(Light lights[], int light_count, unsigned int shader_program)
{
    for (int i = 0; i < light_count; i++)
    {
        draw_light_source(lights[i], shader_program);
    }
}

