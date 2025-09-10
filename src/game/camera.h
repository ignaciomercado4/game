#ifndef CAMERA_H
#define CAMERA_H

#include "../math/math_n.h"
#include <stdbool.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct
{
    bool free;
    float speed;
    float FOV;
    float yaw;
    float pitch;
    Vec3 eye;
    Vec3 center;
    Vec3 up;
    Vec3 right;
} Camera;

extern Vec3 right;
extern Vec3 front;
extern Vec3 up;
extern Vec3 world_up;

Mat4 get_camera_view_matrix(Camera c);
Mat4 get_camera_projection_matrix(Camera c);
void camera_move(Camera *c, Vec3 direction, float delta_time);
void update_camera_vectors(Camera *c);
void camera_point(Camera *c, GLFWwindow *window, float delta_time);

#endif