#include "projectile_manager.h"
#include "../graphics/texture.h"
#include "../math/math_n.h"
#include "../graphics/shader.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void init_projectiles(ProjectileManager *pm)
{
    for (int i = 0; i < MAX_PROJECTILE_COUNT; i++)
    {
        pm->projectiles[i] = (Projectile){
            .active = 0,
            .direction = VEC3(1.0f, 0.0f, 0.0f),
            .drop = 0.1f,
            .lifetime = 2.0f,
            .position = VEC3(0.0f, 0.0f, 0.0f),
            .speed = 0.1f,
            .texture = load_texture("./resources/textures/bullet.png")};
    }
}

void generate_projectile(ProjectileManager *pm, Vec3 position, Vec3 direction)
{
    for (int i = 0; i < MAX_PROJECTILE_COUNT; i++)
    {
        if (pm->projectiles[i].active == 0)
        {
            pm->projectiles[i].active = 1;
            pm->projectiles[i].position = position;
            pm->projectiles[i].direction = direction;
            break;
        }
    }
}

void update_projectile(ProjectileManager *pm, float delta)
{
    for (int i = 0; i < MAX_PROJECTILE_COUNT; i++)
    {

        if (pm->projectiles[i].lifetime <= 0.0f && pm->projectiles[i].active == 0)
        {
            pm->projectiles[i].lifetime = 2.0f;
        }
        if (pm->projectiles[i].active == 1)
        {
            Projectile *p = &pm->projectiles[i];

            if (p->lifetime <= 0.0f)
            {
                p->active = 0;
                continue;
            }

            p->lifetime -= delta;
            Vec3 mul = vec3_scale(p->direction, (p->speed * delta));
            p->position = vec3_add(p->position, mul);
        }

    }
}

void draw_projectiles(ProjectileManager *pm, unsigned int shader)
{
    for (int i = 0; i < MAX_PROJECTILE_COUNT; i++)
    {
        if (pm->projectiles[i].active == 1)
        {
            Projectile *p = &pm->projectiles[i];
            printf("DRAWING PROJECTILE at %f %f %f\n", p->position.x, p->position.y, p->position.z);
            use_shader(shader);
            Mat4 model = mat4_identity();
            model = mat4_translate(model, p->position);
            model = mat4_scale(model, VEC3(0.1f, 0.1f, 0.1f));
            set_mat4_uniform(shader, model, "u_M");
            set_int_uniform(shader, 0, "u_texture");

            glBindTexture(GL_TEXTURE_2D, p->texture.id);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}
