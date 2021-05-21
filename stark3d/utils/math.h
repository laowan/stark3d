#pragma once

#include "global.h"
#include "linmath.h"
#include "memory.h" // memcpy

SK_BEGIN_NAMESPACE

const float PI = 3.1415926;

inline float Radian(float angle)
{
    return angle * PI / 180.0f;
}

class Vector2
{
public:
    float x, y;
    
    Vector2() : x(0.0f), y(0.0f) {}
};

class Vector3
{
public:
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) { }
    Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) { }

    void set(const float x, const float y, const float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator==(const Vector3 &v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
    bool operator!=(const Vector3 &v) const { return !(*this == v); }
    
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    
    Vector3 operator+(const Vector3 &v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 &operator+=(const Vector3 &v) { return *this = *this + v; }
    
    Vector3 operator-(const Vector3 &v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 &operator-=(const Vector3 &v) { return *this = *this - v; }

    Vector3 operator*(const float f) const  { return Vector3(x * f, y * f, z * f); }
    Vector3 &operator*=(const float f) { x *= f; y *= f; z *= f; return *this; }

    Vector3 operator/(const float f) const { return Vector3(x / f, y / f, z / f); }
    Vector3 &operator/=(const float f) { x /= f; y /= f; z /= f; return *this; }

    // ----------------
    // Special products
    // ----------------
    float dot(const Vector3 &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 cross(const Vector3 &v) const
    {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    // ----------------
    // Other operations
    // ----------------
    float length() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    float sqrLength() const
    {
        return x * x + y * y + z * z;
    }

    Vector3 normalized() const
    {
        float l = length();
        if (l < 0.000001f)
        {
            return Vector3(0.0f, 0.0f, 0.0f);
        }
        float invLen = 1.0f / l;
        return Vector3(x * invLen, y * invLen, z * invLen);
    }

    void normalize()
    {
        float l = length();
        if (l < 0.000001f)
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            return;
        }

        float invLen = 1.0f / l;
        x *= invLen;
        y *= invLen;
        z *= invLen;
    }

    static Vector3 Normalize(const Vector3& v)
    {
        return v.normalized();
    }

    Vector3 lerp(const Vector3 &v, float f) const
    {
        return Vector3(x + (v.x - x) * f, y + (v.y - y) * f, z + (v.z - z) * f);
    }

    static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
    {
        return a.lerp(b, f);
    }
};

inline Vector3 operator*(float t, const Vector3 &v) { return Vector3(v.x * t, v.y * t, v.z * t); }
inline Vector3 operator*(const Vector3& a, const Vector3& b) { return Vector3(a.x * b.x, a.y * b.y, a.z * b.z); }
inline float dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

class Vector4
{
public:
    float x, y, z, w;

    Vector4() : x(0), y(0), z(0), w(0)
    {
    }

    explicit Vector4(const float x, const float y, const float z, const float w) :
        x(x), y(y), z(z), w(w)
    {
    }

    explicit Vector4(Vector3 v) : x(v.x), y(v.y), z(v.z), w(1.0f)
    {
    }

    Vector4 operator+(const Vector4 &v) const
    {
        return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    Vector4 operator-(const Vector4 &v) const
    {
        return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    Vector4 operator-() const
    {
        return Vector4(-x, -y, -z, -w);
    }

    Vector4 operator*(const float f) const
    {
        return Vector4(x * f, y * f, z * f, w * f);
    }

    Vector4 operator/(const float f) const
    {
        return Vector4(x / f, y / f, z / f, w / f);
    }

    bool operator==(const Vector4& right) const
    {
        return (x == right.x) &&
               (y == right.y) &&
               (z == right.z) &&
               (w == right.w);
    }

    bool operator!=(const Vector4& right) const
    {
        return !(*this == right);
    }

    void set(const float x, const float y, const float z, const float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};


class Matrix4
{
public:

    mat4x4 m;

    Matrix4()
    {
        mat4x4_identity(m);
    }

    Matrix4(const float *floatArray16)
    {
        for (unsigned int i = 0; i < 4; ++i)
        {
            for (unsigned int j = 0; j < 4; ++j)
            {
                m[i][j] = floatArray16[i * 4 + j];
            }
        }
    }

    Matrix4& operator=(const Matrix4& mat)
    {
        memcpy(m, mat.m, sizeof(mat4x4));
        return *this;
    }

    Matrix4 operator*(const Matrix4& mat) const
    {
        Matrix4 retMat;
        mat4x4_mul(retMat.m, (vec4*)m, (vec4*)mat.m);
        return retMat;
    }

    static Matrix4 LookAtMat(const Vector3& eye, const Vector3& target, const Vector3& up)
    {
        Matrix4 m;
        //Matrix4::LookAt(m, eye, target, up);
        return m;
    }

    static Matrix4 RotMat(float x, float y, float z) // x, y, z in radians
    {
        mat4x4 m1, m2;
        mat4x4_identity(m1);
        mat4x4_identity(m2);
        mat4x4_rotate_Y(m2, m1, y); // rotate y

        mat4x4_rotate_X(m1, m2, x); // rotate x

        Matrix4 ret;
        mat4x4_rotate_Z(ret.m, m1, z); // rotate z
        return ret;
    }
};

class Quaternion
{
public:
    union
    {
        quat qua;
        struct { float x, y, z, w; };
    };

    Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Quaternion(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
};

SK_END_NAMESPACE
