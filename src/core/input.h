#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../game/camera.h"
#include "../game/level.h"
#include "../game/projectile_manager.h"

void process_keyboard_input(GLFWwindow *window, Camera *camera, Level *level, ProjectileManager *pm, float delta_time);

#endif