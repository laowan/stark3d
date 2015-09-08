#ifndef SK_GEOM_H
#define SK_GEOM_H

#include "global.h"
#include <iostream>

SK_BEGIN_NAMESPACE

struct Point2
{
    Point2() : x(0.0), y(0.0) {}
    Point2(float x, float y) { this->x = x; this->y = y; }
    float x, y;
};

class Point3
{
public:
    Point3() : x(0.0), y(0.0), z(0.0) {}
    Point3(float f) : x(f), y(f), z(f) {}
    Point3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

    Point3& operator+=(Point3 pnt);
    Point3& operator-=(Point3 pnt);
    Point3& operator/=(float f);
    Point3& operator*=(float f);

    friend std::ostream& operator<<(std::ostream&, const Point3&);

public:
    float x, y, z;
};

Point3 operator+(Point3 pnt1, Point3 pnt2);
Point3 operator-(Point3 pnt1, Point3 pnt2);
Point3 operator*(Point3 pnt1, float f);
Point3 operator/(Point3 pnt1, float f);

SK_END_NAMESPACE
#endif SK_GEOM_H
