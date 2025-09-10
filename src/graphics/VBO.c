#include "VBO.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

VBO vbo_create(const void *data, size_t size, GLenum type)
{
    VBO vbo;
    vbo.type = type;
    glGenBuffers(1, &vbo.id);

    glBindBuffer(vbo.type, vbo.id);
    glBufferData(vbo.type, size, data, GL_STATIC_DRAW);

    return vbo;
}

void vbo_bind(VBO self)
{
    glBindBuffer(self.type, self.id);
}

void vbo_unbind(VBO self)
{
    glBindBuffer(self.type, 0);
}

void vbo_delete(VBO self)
{
    glDeleteBuffers(1, &self.id);
}
