#include "shader.h"
#include "../core/utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

unsigned int load_shader(const char *path_vs, const char *path_fs)
{
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char *vs_source = read_file_to_string(path_vs);
    glShaderSource(vertex_shader, 1, &vs_source, NULL);
    glCompileShader(vertex_shader);
    check_compile_errors(vertex_shader);

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs_source = read_file_to_string(path_fs);
    glShaderSource(fragment_shader, 1, &fs_source, NULL);
    glCompileShader(fragment_shader);
    check_compile_errors(fragment_shader);

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);

    return shader_program;
}

void use_shader(unsigned int program_id)
{
    glUseProgram(program_id);
}

int check_compile_errors(unsigned int shader_id)
{
    GLint result = GL_FALSE;
    int info_log_length;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    int params = -1;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params)
    {
        int max_length = 2048, actual_length = 0;
        char slog[2048];
        glGetShaderInfoLog(shader_id, max_length, &actual_length, slog);
        printf("ERROR: Shader index %u did not compile.\n%s\n", shader_id, slog);
        return 1;
    }

    return 0;
}

int check_linking_errors(unsigned int program_id)
{
    int params = -1;

    glGetProgramiv(program_id, GL_LINK_STATUS, &params);
    if (GL_TRUE != params)
    {
        int max_length = 2048, actual_length = 0;
        char plog[2048];
        glGetProgramInfoLog(program_id, max_length, &actual_length, plog);
        printf("ERROR: Could not link shader program GL index %u.\n%s\n", program_id, plog);
        return 1;
    }

    return 0;
}

int set_mat4_uniform(unsigned int program_id, Mat4 m, const char *name)
{
    int location = glGetUniformLocation(program_id, name);
    if (location == -1)
    {
        printf("Unable to locate uniform type Mat4 named %s\n", name);
        return 1;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &m.m[0]);

    return 0;
}

int set_vec3_uniform(unsigned int program_id, Vec3 v, const char *name)
{
    int location = glGetUniformLocation(program_id, name);
    if (location == -1)
    {
        printf("Unable to locate uniform type Vec3 named %s\n", name);
        return 1;
    }

    glUniform3fv(location, 1, (GLfloat*)&v);

    return 0;
}

int set_vec2_uniform(unsigned int program_id, Vec2 v, const char *name)
{
    int location = glGetUniformLocation(program_id, name);
    if (location == -1)
    {
        printf("Unable to locate uniform type Vec2 named %s\n", name);
        return 1;
    }

    glUniform2fv(location, 1, (GLfloat*)&v);

    return 0;
}

int set_int_uniform(unsigned int program_id, int i, const char *name)
{
    int location = glGetUniformLocation(program_id, name);
    if (location == -1)
    {
        printf("Unable to locate uniform type int named %s\n", name);
        return 1;
    }

    glUniform1i(location, i);

    return 0;
}

int set_float_uniform(unsigned int program_id, float f, const char *name)
{
    int location = glGetUniformLocation(program_id, name);
    if (location == -1)
    {
        printf("Unable to locate uniform type int named %s\n", name);
        return 1;
    }

    glUniform1f(location, f);

    return 0;
}
