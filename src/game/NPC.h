#ifndef ENEMY_H
#define ENEMY_H

#include "../math/math_n.h"
#include "../graphics/texture.h"

typedef struct
{
    Vec3 position;
    Texture texture;
} NPC;

void draw_NPC(NPC self, Vec3 player_position, unsigned int shader_program);
void draw_NPCs(NPC npcs[], unsigned int count, unsigned int shader_program, Vec3 player_position);

#endif