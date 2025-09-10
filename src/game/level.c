#include <stdio.h>
#include <stdlib.h>
#include "level.h"
#include "wall.h"
#include "../graphics/light.h"
#include "camera.h"
#include "../graphics/shader.h"
#include "../graphics/VAO.h"
#include "NPC.h"
#include "../core/utils.h"

void save_level(const char *path, Level *level)
{
    FILE *lf = fopen(path, "wb");
    if (lf != NULL)
    {
        fwrite(level, sizeof(Level), 1, lf);
        fclose(lf);
    }
    else
    {
        printf("Unable to save level at %s\n", path);
        exit(1);
    }
}

Level load_level_from_file(const char *path)
{
    FILE *lf = fopen(path, "rb");
    if (lf != NULL)
    {
        Level level;
        fread(&level, sizeof(Level), 1, lf);
        fclose(lf);

        printf("Loaded level at %s with %i walls, %i NPC's and %i lights \n", path, level.wall_count, level.NPC_count, level.light_count);

        return level;
    }
    else
    {
        printf("Unable to load level at %s\n", path);
        exit(1);
    }
}

void draw_level(Level *self, Camera *camera,
                unsigned int wall_shader,
                unsigned int floor_shader,
                unsigned int light_shader,
                unsigned int NPC_shader,
                VAO quad_vao,
                VAO cube_vao)
{
    Mat4 V = get_camera_view_matrix(*camera);
    Mat4 P = get_camera_projection_matrix(*camera);

    // Walls
    use_shader(wall_shader);
    set_mat4_uniform(wall_shader, V, "u_V");
    set_mat4_uniform(wall_shader, P, "u_P");
    vao_bind(quad_vao);
    draw_walls(self->walls, self->wall_count, wall_shader);

    // Floors
    use_shader(floor_shader);
    set_mat4_uniform(wall_shader, V, "u_V");
    set_mat4_uniform(wall_shader, P, "u_P");
    vao_bind(quad_vao);
    draw_floors(self->floors, self->floor_count, floor_shader);

    // NPCs
    use_shader(NPC_shader);
    set_mat4_uniform(NPC_shader, V, "u_V");
    set_mat4_uniform(NPC_shader, P, "u_P");
    vao_bind(quad_vao);
    draw_NPCs(self->npcs, self->NPC_count, NPC_shader, camera->eye);

    // Lights
    use_shader(light_shader);
    set_mat4_uniform(light_shader, V, "u_V");
    set_mat4_uniform(light_shader, P, "u_P");
    vao_bind(cube_vao);
    draw_lights(self->lights, self->light_count, light_shader);
}