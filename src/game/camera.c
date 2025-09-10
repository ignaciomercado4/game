#include "camera.h"
#include "../math/math_n.h"
#include <math.h>
#include <stdbool.h>

Vec3 front = VEC3(0.0f, 0.0f, -1.0f);
Vec3 up = VEC3(0.0f, 1.0f, 0.0f);
Vec3 right = VEC3(-1.0f, 0.0f, 0.0f);
Vec3 world_up = VEC3(0.0f, 1.0f, 0.0f);

Mat4 get_camera_view_matrix(Camera c)
{
    return mat4_look_at(c.eye, c.center, c.up);
}

Mat4 get_camera_projection_matrix(Camera c)
{
    return mat4_projection(c.FOV, (float)1920/(float)1080, 0.01f, 100.0f);
}

void camera_move(Camera *c, Vec3 direction, float delta_time)
{
    float velocity = c->speed * delta_time;
    Vec3 movement = vec3_scale(direction, velocity);

    c->eye    = vec3_add(c->eye, movement);
    c->center = vec3_add(c->center, movement);
}

void update_camera_vectors(Camera *c)
{
    Vec3 front;
    front.x = cosf(radians(c->yaw)) * cosf(radians(c->pitch));
    front.y = sinf(radians(c->pitch));
    front.z = sinf(radians(c->yaw)) * cosf(radians(c->pitch));
    front = vec3_normalize(front);

    c->center = vec3_add(c->eye, front);
    c->right  = vec3_normalize(vec3_cross(front, world_up));
    c->up     = vec3_normalize(vec3_cross(c->right, front));
}

void camera_point(Camera *c, GLFWwindow *window, float delta_time)
{
    float rotate_speed = 50.0f * delta_time; 

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        c->pitch += rotate_speed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        c->pitch -= rotate_speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        c->yaw   -= rotate_speed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        c->yaw   += rotate_speed;

    if (c->pitch > 89.0f)  c->pitch = 89.0f;
    if (c->pitch < -89.0f) c->pitch = -89.0f;

    update_camera_vectors(c);
}

