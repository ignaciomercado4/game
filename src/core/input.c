#include "input.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../game/camera.h"
#include "../math/math_n.h"
#include <stdio.h>

void process_keyboard_input(GLFWwindow *window, Camera *camera, float delta_time)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    {
        camera->free = !(camera->free);
    }

    if (!camera->free)
    {
        camera->eye.y = 2.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_move(camera, vec3_sub(camera->center, camera->eye), delta_time); 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_move(camera, vec3_negate(vec3_sub(camera->center, camera->eye)), delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_move(camera, vec3_negate(camera->right), delta_time); 
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_move(camera, camera->right, delta_time);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        printf("Shot!\n");
}