#include "wall.h"
#include "../math/math_n.h"
#include "../graphics/shader.h"
#include <math.h>
#include <GL/glew.h>

#include <GLFW/glfw3.h>

void draw_wall(Wall self, unsigned int shader_program)
{
    use_shader(shader_program);

    // calculates full wall length and height
    float wall_length = sqrtf(
        powf(self.start_coordinates.x - self.end_coordinates.x, 2) +
        powf(self.start_coordinates.z - self.end_coordinates.z, 2));
    float wall_height = fabsf(self.end_coordinates.y - self.start_coordinates.y);

    // gets the wall's middle point world space coordinates. This middle point is basically 1/2 the length
    // of the hypotenuse formed by the wall's bottom and left sides 
    Vec3 mid_point = get_wall_worldspace_coordinates(self.start_coordinates, self.end_coordinates);
    
    // generate model matrix
    Mat4 model_matrix = mat4_identity();
    // translate to its world space coordinates
    model_matrix = mat4_translate(model_matrix, mid_point);
    
    // calculate rotation in radians using the start and end points
    float rotation_in_radians = atan2(
        self.end_coordinates.z - self.start_coordinates.z,
        self.end_coordinates.x - self.start_coordinates.x);
    
    // apply rotation and scale to real size
    model_matrix = mat4_rotate(model_matrix, rotation_in_radians, VEC3(0.0f, 1.0f, 0.0f));
    model_matrix = mat4_scale(model_matrix, VEC3(wall_length, wall_height, 1.0f));
    
    // pass texture uniform and bind
    set_int_uniform(shader_program, 0, "u_texture");
    glBindTexture(GL_TEXTURE_2D, self.texture.id);

    // defines tile size, which is the world units that takes to repeat the texture and passes uniform
    float tile_size = 5.0f;
    set_float_uniform(shader_program, tile_size, "u_tile_size");

    // pass model matrix uniform and draws
    set_mat4_uniform(shader_program, model_matrix, "u_M");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void draw_walls(Wall walls[], int count, unsigned int shader_program)
{
    for (int i = 0; i < count; i++)
    {
        draw_wall(walls[i], shader_program);
    }
}

Vec3 get_wall_worldspace_coordinates(Vec3 start, Vec3 end)
{
    float x, y, z;
    x = (start.x + end.x) / 2;
    y = (start.y + end.y) / 2;
    z = (start.z + end.z) / 2;
    return VEC3(x, y, z);
}