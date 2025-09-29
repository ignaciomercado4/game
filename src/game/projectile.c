#include "projectile.h"
#include "../math/math_n.h"
#include "../graphics/shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void update_projectile(Projectile *self, float delta)
{
    printf("Lifetime: %f \n", self->lifetime);
    printf("Position: %f | %f | %f \n", self->position.x, self->position.y, self->position.z);

    if (self->lifetime <= 0.0f)
    {
        self->active = 0;
    }

    self->position = vec3_add(self->position, VEC3(self->speed, 0.0f, 0.0f));
    self->lifetime -= delta;
}

void draw_projectile(Projectile *self, unsigned int shader_program)
{
    if (self->active == 0)
    {
        return;
    }

    Mat4 model = mat4_identity();
    model = mat4_translate(model, self->position);
    model = mat4_scale(model, VEC3(0.1f, 0.1f, 0.1f));
    model = mat4_rotate(model, radians(90.0f), VEC3(0.0f, 0.0f, 1.0f));

    use_shader(shader_program);
    set_mat4_uniform(shader_program, model, "u_M");
    set_int_uniform(shader_program, 0, "u_texture");
    glBindTexture(GL_TEXTURE_2D, self->texture.id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}