#include "collision.h"
#include "../math/math_n.h"
#include "wall.h"
#include "../graphics/shader.h"
#include <stdbool.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Vec3 get_closest_point_on_segment(Vec3 position, Vec3 point_A, Vec3 point_B)
{
    Vec3 ab = vec3_sub(point_B, point_A);
    float t = vec3_dot(vec3_sub(position, point_A), ab) / vec3_dot(ab, ab);
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    if (t > 1.0f)
    {
        t = 1.0f;
    }

    return vec3_add(point_A, vec3_scale(ab, t));
}

bool check_collision_player_wall(Vec3 player_position, Wall wall)
{

    Vec3 closest = get_closest_point_on_segment(player_position, wall.start_coordinates, wall.end_coordinates);
    float dist = vec3_length(vec3_sub(player_position, closest));

    // Beware: hardcoded player radius
    return dist < 0.7f;
}

void draw_collider(Collider self, unsigned int shader_program)
{
    Mat4 model_matrix = mat4_identity();
    model_matrix = mat4_translate(model_matrix, self.position);
    model_matrix = mat4_scale(model_matrix, self.dimensions);
    use_shader(shader_program);
    set_mat4_uniform(shader_program, model_matrix, "u_M");
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void draw_colliders(Collider colliders[], int count, unsigned int shader_program)
{
    for (int i = 0; i < count; i++)
    {
        draw_collider(colliders[i], shader_program);
    }
}

bool sphere_AABB_collision(Vec3 sphere_center, float sphere_radius, Collider collider)
{
    Vec3 half = vec3_scale(collider.dimensions, 0.5f);
    Vec3 min = vec3_sub(collider.position, half);
    Vec3 max = vec3_add(collider.position, half);

    float x = fmaxf(min.x, fminf(sphere_center.x, max.x));
    float y = fmaxf(min.y, fminf(sphere_center.y, max.y));
    float z = fmaxf(min.z, fminf(sphere_center.z, max.z));

    Vec3 closest_point = {x, y, z};

    Vec3 diff = vec3_sub(sphere_center, closest_point);

    return (vec3_dot(diff, diff) <= sphere_radius * sphere_radius);
}
