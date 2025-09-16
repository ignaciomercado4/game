#ifndef ROOF_H
#define ROOF_H

#include "../graphics/texture.h"
#include "../math/math_n.h"

typedef struct
{
    Vec3 start_coordinates;
    Vec3 end_coordinates;
    Texture texture;
} Roof;

void draw_roof(Roof self, unsigned int shader_program);
void draw_roofs(Roof roofs[], int count, unsigned int shader_program);
Vec3 get_roof_worldspace_coordinates(Vec3 start, Vec3 end);

#endif