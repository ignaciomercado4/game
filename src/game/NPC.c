#include "NPC.h"
#include "../graphics/shader.h"
#include "../math/math_n.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

void draw_NPC(NPC self, Vec3 player_position, unsigned int shader_program)
{
    use_shader(shader_program);
    Mat4 model_matrix = mat4_identity();
    model_matrix = mat4_scale(model_matrix, VEC3(2.0f, 2.0f, 2.0f));

    Vec3 look = vec3_sub(player_position, self.position);
    look.y = 0.0f;
    look = vec3_normalize(look);
    float angle = atan2(look.x, look.z);

    model_matrix = mat4_translate(model_matrix, self.position);
    model_matrix = mat4_rotate(model_matrix, angle, VEC3(0.0f, 1.0f, 0.0f));

    model_matrix = mat4_translate(model_matrix, VEC3(self.position.x, 0.0f, self.position.z));
    set_mat4_uniform(shader_program, model_matrix, "u_M");
    set_int_uniform(shader_program, 0, "u_texture");
    glBindTexture(GL_TEXTURE_2D, self.texture.id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void draw_NPCs(NPC npcs[], unsigned int count, unsigned int shader_program, Vec3 player_position)
{
    for (int i = 0; i < count; i++)
    {
        draw_NPC(npcs[0], player_position, shader_program);
    }
}