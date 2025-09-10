#include "window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

GLFWwindow* create_window(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        printf("Error initialising GLFW.\n");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(w);
    if (!w)
    {
        printf("Error creating window.\n");
        glfwTerminate();
        exit(1);
    }
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Error initialising GLEW.\n");
        exit(1);
    }

    return w;
}