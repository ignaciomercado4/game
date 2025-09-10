#ifndef VBO_H
#define VBO_H

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct 
{
    unsigned int id;
    GLenum type;
} VBO;

VBO vbo_create(const void* data, size_t size, GLenum type);
void vbo_bind(VBO self);
void vbo_unbind();
void vbo_delete(VBO self);


#endif