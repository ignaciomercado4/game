#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct
{
    unsigned int id;
} VAO;

VAO vao_create();
void vao_bind(VAO self);
void vao_unbind();
void vao_delete(VAO self);
void vao_set_vertex_attrib_data(
    GLuint index,        // location
    GLint size,          // component count
    GLenum type,         // type
    GLboolean normalized,// normalized?
    GLsizei stride,      // each vertex's size in bytes
    const void* offset   // offset 
);

#endif