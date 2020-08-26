#ifndef SK_GEOM_H
#define SK_GEOM_H

#include "global.h"
#include "math.h"
#include <cmath>

SK_BEGIN_NAMESPACE

class Rect
{
//
//    A +-----------+ B
//      |           |
//      |           |
//    D +-----------+ C
//
public:
    Rect(const Vector3 a, const Vector3 b, const Vector3 c, const Vector3 d):a(a),b(b),c(c),d(d) {}
    Rect(const Vector3 origin, float width, float height, float angle) {}
    
    // return the offset distance use D as the original point
    Vector3 offset(const Vector3 p)
    {
        Vector3 result;

        // distance to AD
        float A = a.y - d.y;
        float B = d.x - a.x;
        float C = a.x * d.y - d.x * a.y;
        result.x = (A * p.x + B * p.y + C) / sqrt(A * A + B * B);

        // distance to DC
        A = d.y - c.y;
        B = c.x - d.x;
        C = d.x * c.y - c.x * d.y;
        result.y = (A * p.x + B * p.y + C) / sqrt(A * A + B * B);

        return result;
    }

private:
    Vector3 a, b, c, d;
    Vector3 origin;
    float w, h;
    float angle;
};

SK_END_NAMESPACE

#endif
