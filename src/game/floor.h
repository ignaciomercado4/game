#ifndef FLOOR_H
#define FLOOR_H

#include "../graphics/texture.h"
#include "../math/math_n.h"

typedef struct
{
    Vec3 start_coordinates;
    Vec3 end_coordinates;
    Texture texture;
} Floor;

void draw_floor(Floor self, unsigned int shader_program);
void draw_floors(Floor floors[], int count, unsigned int shader_program);
Vec3 get_floor_worldspace_coordinates(Vec3 start, Vec3 end);

#endif