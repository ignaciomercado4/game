#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "../graphics/texture.h"
#include "../math/math_n.h"

#define MAX_PROJECTILE_COUNT 100

typedef struct
{
    Texture texture;
    float speed;
    Vec3 position;
    Vec3 direction;
    float lifetime; // in seconds
    float drop;
    int active; // 1 == active, 0 == inactive
} Projectile;

typedef struct
{
    Projectile projectiles[MAX_PROJECTILE_COUNT];
    int count;
} ProjectileManager;

void init_projectiles(ProjectileManager *pm);
void generate_projectile(ProjectileManager *pm, Vec3 position, Vec3 direction);
void update_projectile(ProjectileManager *pm, float delta);
void draw_projectiles(ProjectileManager *pm, unsigned int shader); 


#endif