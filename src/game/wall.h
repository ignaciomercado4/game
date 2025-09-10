#ifndef WALL_H
#define WALL_H

#include "../math/math_n.h"
#include "../graphics/texture.h"

typedef struct
{
    Vec3 start_coordinates;
    Vec3 end_coordinates;
    Texture texture;
} Wall;

void draw_wall(Wall self, unsigned int shader_program);
void draw_walls(Wall walls[], int count, unsigned int shader_program);
Vec3 get_wall_worldspace_coordinates(Vec3 start, Vec3 end);

#endif