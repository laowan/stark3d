#include "geom.h"

SK_BEGIN_NAMESPACE

Point3& Point3::operator+=(Point3 pnt)
{
    x += pnt.x;
    y += pnt.y;
    z += pnt.z;
    return *this;
}

Point3& Point3::operator-=(Point3 pnt)
{
    x -= pnt.x;
    y -= pnt.y;
    z -= pnt.z;
    return *this;
}

Point3& Point3::operator/=(float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

Point3& Point3::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}


std::ostream& operator<<(std::ostream &os, const Point3 &pnt)
{
    os << pnt.x << ',' << pnt.y << ',' << pnt.z;
    return os;
}

Point3 operator+(Point3 pnt1, Point3 pnt2) { return pnt1 += pnt2; }
Point3 operator-(Point3 pnt1, Point3 pnt2) { return pnt1 -= pnt2; }
Point3 operator*(Point3 pnt1, float f) { return pnt1 *= f; }
Point3 operator/(Point3 pnt1, float f) { return pnt1 /= f; }
SK_END_NAMESPACE
