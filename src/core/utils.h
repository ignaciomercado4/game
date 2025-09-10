#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GL_CHECK(stmt)                                 \
    do                                                 \
    {                                                  \
        stmt;                                          \
        check_opengl_error(#stmt, __FILE__, __LINE__); \
    } while (0)

char *read_file_to_string(const char *path);
void check_opengl_error(const char *stmt, const char *fname, int line);
void GLAPIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

#endif