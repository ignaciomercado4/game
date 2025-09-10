#include "floor.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../math/math_n.h"
#include "../graphics/shader.h"
#include <math.h>
#include <stdio.h>

void draw_floor(Floor self, unsigned int shader_program)
{
    use_shader(shader_program);
    Mat4 model_matrix = mat4_identity();
    float x_len = self.end_coordinates.x - self.start_coordinates.x;
    float z_len = self.end_coordinates.y - self.start_coordinates.y;
    float y_len = self.end_coordinates.z - self.start_coordinates.z;
    Vec3 mid_point = get_floor_worldspace_coordinates(self.start_coordinates, self.end_coordinates);
    model_matrix = mat4_translate(model_matrix, mid_point);
    model_matrix = mat4_rotate(model_matrix, radians(90.0f), VEC3(1.0f, 0.0f, 0.0f));
    model_matrix = mat4_scale(model_matrix, VEC3(x_len, y_len, z_len));

    glBindTexture(GL_TEXTURE_2D, self.texture.id);
    set_int_uniform(shader_program, 0, "u_texture");
    set_mat4_uniform(shader_program, model_matrix, "u_M");
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void draw_floors(Floor floors[], int count, unsigned int shader_program)
{
    for (int i  = 0; i < count; i++)
    {
        draw_floor(floors[i], shader_program);
    }
}

Vec3 get_floor_worldspace_coordinates(Vec3 start, Vec3 end)
{
    float x, y, z;
    x = (start.x + end.x) / 2;
    y = (start.y + end.y) / 2;
    z = (start.z + end.z) / 2;
    return VEC3(x, y, z);
}