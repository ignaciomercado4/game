#ifndef SHADER_H
#define SHADER_H

#include "../math/math_n.h"

unsigned int load_shader(const char* path_vs, const char* path_fs);
void use_shader(unsigned int program_id);
int check_compile_errors(unsigned int shader_id);
int check_linking_errors(unsigned int program_id);
int set_mat4_uniform(unsigned int program_id, Mat4 m, const char* name);
int set_vec3_uniform(unsigned int program_id, Vec3 m, const char* name);
int set_vec2_uniform(unsigned int program_id, Vec2 v, const char *name);
int set_int_uniform(unsigned int program_id, int i, const char *name);
int set_float_uniform(unsigned int program_id, float f, const char *name);

#endif