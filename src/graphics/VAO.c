#include "VAO.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

VAO vao_create()
{
    VAO vao;
    glGenVertexArrays(1, &vao.id);
    return vao;
}

void vao_bind(VAO self)
{
    glBindVertexArray(self.id);
}

void vao_unbind()
{
    glBindVertexArray(0);
}

void vao_delete(VAO self)
{
    glDeleteVertexArrays(1, &self.id);
}

void vao_set_vertex_attrib_data(
    GLuint index,         // location
    GLint size,           // component count
    GLenum type,          // type
    GLboolean normalized, // normalized?
    GLsizei stride,       // each vertex's size in bytes
    const void *offset    // offset
)
{
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}