#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../graphics/texture.h"
#include "../math/math_n.h"

typedef struct
{
    Texture texture;
    float speed;
    Vec3 position;
    Vec3 direction;
    float lifetime; // in seconds
    float drop;
    int active; // 1 == active, inactive
} Projectile;


void update_projectile(Projectile *self, float delta);
void draw_projectile(Projectile *self, unsigned int shader_program);

#endif