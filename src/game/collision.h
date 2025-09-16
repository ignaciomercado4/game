#ifndef COLLISION_H
#define COLLISION_H

#include "../math/math_n.h"
#include "wall.h"
#include <stdbool.h>
 
typedef struct 
{
    Vec3 position;
    Vec3 dimensions;
} Collider;

Vec3 get_closest_point_on_segment(Vec3 position, Vec3 point_A, Vec3 point_B);
bool check_collision_player_wall(Vec3 player_position, Wall wall);
void draw_collider(Collider self, unsigned int shader_program);
void draw_colliders(Collider colliders[], int count, unsigned int shader_program);
bool sphere_AABB_collision(Vec3 center, float radius, Collider box);

#endif