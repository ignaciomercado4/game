#ifndef LEVEL_H
#define LEVEL_H

#include "wall.h"
#include "NPC.h"
#include "../graphics/light.h"
#include "camera.h"
#include "../graphics/VAO.h"
#include "floor.h"
#define MAX_LEVEL_WALL_COUNT 64
#define MAX_LEVEL_FLOOR_COUNT 32
#define MAX_LEVEL_ENEMY_COUNT 16
#define MAX_LEVEL_LIGHT_COUNT 16


typedef struct
{
    int wall_count;
    int floor_count;
    int NPC_count;
    int light_count;
    NPC npcs[MAX_LEVEL_ENEMY_COUNT];
    Wall walls[MAX_LEVEL_WALL_COUNT];
    Floor floors[MAX_LEVEL_FLOOR_COUNT];
    Light lights[MAX_LEVEL_LIGHT_COUNT];
} Level;

void save_level(const char *path, Level *level);
Level load_level_from_file(const char* path);
void draw_level(Level *self, Camera *camera, 
                unsigned int wall_shader, 
                unsigned int floor_shader, 
                unsigned int light_shader, 
                unsigned int NPC_shader, 
                VAO quad_vao, 
                VAO cube_vao);

#endif