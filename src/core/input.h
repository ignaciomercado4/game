#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../game/camera.h"

void process_keyboard_input(GLFWwindow* window, Camera *camera, float delta_time);

#endif