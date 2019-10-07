#ifndef SK_MATH_H
#define SK_MATH_H

#include "global.h"

SK_BEGIN_NAMESPACE

class Vec3f
{
public:
    float x, y, z;

    Vec3f() : x(0.0f), y(0.0f), z(0.0f) { }
    Vec3f(const float x, const float y, const float z) : x(x), y(y), z(z) { }
    Vec3f(const Vec3f &v) : x(v.x), y(v.y), z(v.z) { }

    void set(const float x, const float y, const float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator==(const Vec3f &v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
    bool operator!=(const Vec3f &v) const { return !(*this == v); }
    
    Vec3f operator-() const { return Vec3f(-x, -y, -z); }
    
    Vec3f operator+(const Vec3f &v) const { return Vec3f(x + v.x, y + v.y, z + v.z); }
    Vec3f &operator+=(const Vec3f &v) { return *this = *this + v; }
    
    Vec3f operator-(const Vec3f &v) const { return Vec3f(x - v.x, y - v.y, z - v.z); }
    Vec3f &operator-=(const Vec3f &v) { return *this = *this - v; }

    Vec3f operator*(const float f) const  { return Vec3f(x * f, y * f, z * f); }
    Vec3f &operator*=(const float f) { x *= f; y *= f; z *= f; return *this; }

    Vec3f operator/(const float f) const { return Vec3f(x / f, y / f, z / f); }
    Vec3f &operator/=(const float f) { x /= f; y /= f; z /= f; return *this; }

    // ----------------
    // Special products
    // ----------------
    float dot(const Vec3f &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3f cross(const Vec3f &v) const
    {
        return Vec3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
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

    Vec3f normalized() const
    {
        float l = length();
        if (l < 0.000001f)
        {
            return Vec3f(0.0f, 0.0f, 0.0f);
        }
        float invLen = 1.0f / l;
        return Vec3f(x * invLen, y * invLen, z * invLen);
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

    static Vec3f Normalize(const Vec3f& v)
    {
        return v.normalized();
    }

    Vec3f lerp(const Vec3f &v, float f) const
    {
        return Vec3f(x + (v.x - x) * f, y + (v.y - y) * f, z + (v.z - z) * f);
    }

    static Vec3f Lerp(const Vec3f& a, const Vec3f& b, float f)
    {
        return a.lerp(b, f);
    }
};

inline Vec3f operator*(float t, const Vec3f &v) { return Vec3f(v.x * t, v.y * t, v.z * t); }
inline float dot(const Vec3f& v1, const Vec3f& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

class Vec4f
{
public:
    float x, y, z, w;

    Vec4f() : x(0), y(0), z(0), w(0)
    {
    }

    explicit Vec4f(const float x, const float y, const float z, const float w) :
        x(x), y(y), z(z), w(w)
    {
    }

    explicit Vec4f(Vec3f v) : x(v.x), y(v.y), z(v.z), w(1.0f)
    {
    }

    Vec4f operator+(const Vec4f &v) const
    {
        return Vec4f(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    Vec4f operator-(const Vec4f &v) const
    {
        return Vec4f(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    Vec4f operator-() const
    {
        return Vec4f(-x, -y, -z, -w);
    }

    Vec4f operator*(const float f) const
    {
        return Vec4f(x * f, y * f, z * f, w * f);
    }

    Vec4f operator/(const float f) const
    {
        return Vec4f(x / f, y / f, z / f, w / f);
    }

    bool operator==(const Vec4f& right) const
    {
        return (x == right.x) &&
               (y == right.y) &&
               (z == right.z) &&
               (w == right.w);
    }

    bool operator!=(const Vec4f& right) const
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


class Mat4f
{
public:
    union
    {
        float c[4][4];	// Column major order for OpenGL: c[column][row]
        float x[16];
    };

    Mat4f()
    {
        c[0][0] = 1; c[1][0] = 0; c[2][0] = 0; c[3][0] = 0;
        c[0][1] = 0; c[1][1] = 1; c[2][1] = 0; c[3][1] = 0;
        c[0][2] = 0; c[1][2] = 0; c[2][2] = 1; c[3][2] = 0;
        c[0][3] = 0; c[1][3] = 0; c[2][3] = 0; c[3][3] = 1;
    }

    Mat4f(const float *floatArray16)
    {
        for (unsigned int i = 0; i < 4; ++i)
        {
            for (unsigned int j = 0; j < 4; ++j)
            {
                c[i][j] = floatArray16[i * 4 + j];
            }
        }
    }

    static Mat4f LookAtMat(const Vec3f& eye, const Vec3f& target, const Vec3f& up)
    {
        Mat4f m;
        //Mat4f::LookAt(m, eye, target, up);
        return m;
    }
};

SK_END_NAMESPACE

#endif
