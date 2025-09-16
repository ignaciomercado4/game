#ifndef MATH_N_H
#define MATH_N_H

// Common constants and helper macros
#define MATH_PI 3.14159265358979323846
#define VEC2(x, y)   ((Vec2){ (x), (y) })       // Macro to create a Vec2
#define VEC3(x, y, z) ((Vec3){ (x), (y), (z) }) // Macro to create a Vec3
#define VEC4(x, y, z, w) ((Vec4){ (x), (y), (z), (w) }) // Macro to create a Vec4

/* ================================
   Struct Definitions
   ================================ */

// 2D Vector (only x and z components are defined)
typedef struct {
    float x, z;
} Vec2;

// 3D Vector
typedef struct {
    float x, y, z;
} Vec3;

// 4D Vector
typedef struct {
    float x, y, z, w;
} Vec4;

// 4x4 Matrix
typedef struct {
    float m[16];
} Mat4;

/* ================================
   Vec3 Functions
   ================================ */
Vec3 vec3_new(float x, float y, float z);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(Vec3 v, float s);
Vec3 vec3_normalize(Vec3 v);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec3 vec3_negate(Vec3 v);
float vec3_length(Vec3 v);
float vec3_distance(Vec3 a, Vec3 b);
float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_lerp(Vec3 a, Vec3 b, float t);

/* ================================
   Vec4 Functions
   ================================ */
Vec4 vec4_new(float x, float y, float z, float w);
Vec4 vec4_add(Vec4 a, Vec4 b);
Vec4 vec4_sub(Vec4 a, Vec4 b);
Vec4 vec4_scale(Vec4 v, float s);
float vec4_dot(Vec4 a, Vec4 b);

/* ================================
   Mat4 Functions
   ================================ */
Mat4 mat4_scalar(float val);
Mat4 mat4_identity();
Mat4 mat4_translate(Mat4 m, Vec3 v);
Mat4 mat4_scale(Mat4 m, Vec3 v);
Mat4 mat4_rotate(Mat4 m, float angle, Vec3 axis);
Mat4 mat4_mul(Mat4 a, Mat4 b);
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);
Mat4 mat4_projection(float fovy, float ratio, float near, float far);
Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up);

/* ================================
   Miscellaneous
   ================================ */
float radians(float deg);
float clamp(float value, float min, float max);

#endif
