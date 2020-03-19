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
    Rect(const Vec2f a, const Vec2f b, const Vec2f c, const Vec2f d):a(a),b(b),c(c),d(d) {}
    Rect(const Vec2f origin, float width, float height, float angle) {}
    
    // return the offset distance use D as the original point
    Vec2f offset(const Vec2f p)
    {
        Vec2f result;

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
    Vec2f a, b, c, d;
    Vec2f origin;
    float w, h;
    float angle;
};

SK_END_NAMESPACE

#endif
