#ifndef _BBOX_H
#define _BBOX_H

#include "global.h"
SK_BEGIN_NAMESPACE

class BBox
{
    struct Point
    {
        Point(float x, float y, float z) : _x(x), _y(y), _z(z) {}
        float _x, _y, _z;
    };

public:
    BBox();
    void add(float x, float y, float z);
    bool render();

private:
    float _xmin, _xmax;
    float _ymin, _ymax;
    float _zmin, _zmax;

    bool _dirty;
};

SK_END_NAMESPACE

#endif