#ifndef LIGHT_H
#define LIGHT_H

#include "../math/math_n.h"

typedef struct 
{
    Vec3 position;
    Vec3 color;
} Light;

void draw_light_source(Light self, unsigned int shader_program);
void draw_lights(Light lights[], int light_count, unsigned int shader_program);

#endif