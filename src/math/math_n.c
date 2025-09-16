#include "math_n.h"
#include <stdlib.h>
#include <math.h>

/* =============================
   Vector 3 (Vec3) functions
   ============================= */

// Create a new 3D vector
Vec3 vec3_new(float x, float y, float z)
{
    Vec3 new;
    new.x = x;
    new.y = y;
    new.z = z;

    return new;
}

// Add two 3D vectors
Vec3 vec3_add(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

// Subtract two 3D vectors
Vec3 vec3_sub(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

// Multiply vector by scalar
Vec3 vec3_scale(Vec3 v, float s)
{
    Vec3 result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;

    return result;
}

// Normalize a vector (unit length)
Vec3 vec3_normalize(Vec3 v)
{
    Vec3 result;
    float len = vec3_length(v);

    if (len == 0.0f)
    {
        result = (Vec3){0.0f, 0.0f, 0.0f}; // return zero vector if length is zero
        return result;
    }

    result.x = v.x / len;
    result.y = v.y / len;
    result.z = v.z / len;

    return result;
}

// Cross product of two vectors
Vec3 vec3_cross(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

// Negate vector (reverse direction)
Vec3 vec3_negate(Vec3 v)
{
    Vec3 result;
    result.x = -v.x;
    result.y = -v.y;
    result.z = -v.z;

    return result;
}

// Vector length (magnitude)
float vec3_length(Vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Distance between two vectors
float vec3_distance(Vec3 a, Vec3 b)
{
    return vec3_length(vec3_sub(a, b));
}

// Dot product of two vectors
float vec3_dot(Vec3 a, Vec3 b)
{
    float result = (a.x * b.x) +
                   (a.y * b.y) +
                   (a.z * b.z);

    return result;
}

// Lerp
Vec3 vec3_lerp(Vec3 a, Vec3 b, float t)
{
    return (Vec3){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    };
}


/* =============================
   Vector 4 (Vec4) functions
   ============================= */

// Create new 4D vector
Vec4 vec4_new(float x, float y, float z, float w)
{
    Vec4 new;
    new.x = x;
    new.y = y;
    new.z = z;
    new.w = w;

    return new;
}

// Add two 4D vectors
Vec4 vec4_add(Vec4 a, Vec4 b)
{
    Vec4 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

// Subtract two 4D vectors
Vec4 vec4_sub(Vec4 a, Vec4 b)
{
    Vec4 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

// Multiply vector by scalar
Vec4 vec4_scale(Vec4 v, float s)
{
    Vec4 result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    result.w = v.w * s;
    return result;
}

// Dot product of two 4D vectors
float vec4_dot(Vec4 a, Vec4 b)
{
    float result = (a.x * b.x) +
                   (a.y * b.y) +
                   (a.z * b.z) +
                   (a.w * b.w);

    return result;
}


/* =============================
   Matrix 4x4 (Mat4) functions
   ============================= */

// Create diagonal matrix with scalar value
Mat4 mat4_scalar(float val)
{
    Mat4 result = {0};
    result.m[0] = val;
    result.m[5] = val;
    result.m[10] = val;
    result.m[15] = val;

    return result;
}

// Create identity matrix
Mat4 mat4_identity()
{
    Mat4 result = {0};
    result.m[0] = 1.0f;
    result.m[5] = 1.0f;
    result.m[10] = 1.0f;
    result.m[15] = 1.0f;

    return result;
}

// Translation matrix (applies translation to m)
Mat4 mat4_translate(Mat4 m, Vec3 v)
{
    Mat4 T = mat4_identity();
    T.m[12] = v.x;
    T.m[13] = v.y;
    T.m[14] = v.z;

    return mat4_mul(m, T);
}

// Scaling matrix
Mat4 mat4_scale(Mat4 m, Vec3 v)
{
    Mat4 S = mat4_identity();
    S.m[0]  = v.x;
    S.m[5]  = v.y;
    S.m[10] = v.z;

    return mat4_mul(m, S);
}

// Rotation matrix (angle in radians, axis normalized)
Mat4 mat4_rotate(Mat4 m, float angle, Vec3 axis)
{
    axis = vec3_normalize(axis);

    float c = cosf(angle);
    float s = sinf(angle);
    float one_c = 1.0f - c;

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    Mat4 R = mat4_identity();

    R.m[0] = c + x * x * one_c;
    R.m[1] = y * x * one_c + z * s;
    R.m[2] = z * x * one_c - y * s;
    R.m[3] = 0.0f;

    R.m[4] = x * y * one_c - z * s;
    R.m[5] = c + y * y * one_c;
    R.m[6] = z * y * one_c + x * s;
    R.m[7] = 0.0f;

    R.m[8] = x * z * one_c + y * s;
    R.m[9] = y * z * one_c - x * s;
    R.m[10] = c + z * z * one_c;
    R.m[11] = 0.0f;

    R.m[12] = 0.0f;
    R.m[13] = 0.0f;
    R.m[14] = 0.0f;
    R.m[15] = 1.0f;

    return mat4_mul(m, R);
}

// Multiply two 4x4 matrices
Mat4 mat4_mul(Mat4 a, Mat4 b)
{
    Mat4 result = {0};

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            result.m[col * 4 + row] =
                a.m[0 * 4 + row] * b.m[col * 4 + 0] +
                a.m[1 * 4 + row] * b.m[col * 4 + 1] +
                a.m[2 * 4 + row] * b.m[col * 4 + 2] +
                a.m[3 * 4 + row] * b.m[col * 4 + 3];
        }
    }

    return result;
}

// Multiply 4x4 matrix with 4D vector
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v)
{
    Vec4 result;
    result.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12] * v.w;
    result.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13] * v.w;
    result.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14] * v.w;
    result.w = m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15] * v.w;

    return result;
}

// Perspective projection matrix
Mat4 mat4_projection(float fovy, float aspect, float near, float far)
{
    Mat4 result = {0};
    float tanHalfFovy = tanf(fovy / 2.0f);

    result.m[0] = 1.0f / (aspect * tanHalfFovy);
    result.m[5] = 1.0f / (tanHalfFovy);
    result.m[10] = -(far + near) / (far - near);
    result.m[11] = -1.0f;
    result.m[14] = -(2.0f * far * near) / (far - near);
    result.m[15] = 0.0f;

    return result;
}

// View matrix using eye position, target and up vector
Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up)
{
    Mat4 result = {0};
    Vec3 x, y, z;

    // Compute forward, right, up
    z = vec3_sub(eye, center);
    z = vec3_normalize(z);
    y = up;
    x = vec3_cross(y, z);
    y = vec3_cross(z, x);

    x = vec3_normalize(x);
    y = vec3_normalize(y);

    // Fill matrix
    result.m[0] = x.x;
    result.m[1] = y.x;
    result.m[2] = z.x;
    result.m[3] = 0.0f;

    result.m[4] = x.y;
    result.m[5] = y.y;
    result.m[6] = z.y;
    result.m[7] = 0.0f;

    result.m[8] = x.z;
    result.m[9] = y.z;
    result.m[10] = z.z;
    result.m[11] = 0.0f;

    result.m[12] = -vec3_dot(x, eye);
    result.m[13] = -vec3_dot(y, eye);
    result.m[14] = -vec3_dot(z, eye);
    result.m[15] = 1.0f;

    return result;
}


/* =============================
   Misc functions
   ============================= */

// Convert degrees to radians
float radians(float deg)
{
    return deg * (MATH_PI / 180.0f);
}

float clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}