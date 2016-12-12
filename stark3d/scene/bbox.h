#ifndef _BBOX_H
#define _BBOX_H

#include "global.h"
#include "geom.h"
#include "renderaction.h"
#include <vector>

#define BBOX_LIMIT 1.0e+12

SK_BEGIN_NAMESPACE

class STARK_API BBox
{
public:
    BBox();
    void add(float x, float y, float z);
    bool render(RenderAction* act);
    Point3 maxPoint() const;
    Point3 minPoint() const;
    std::vector<Point3> points() const;
    void getSixPlanes(Point3 *pnts, Point3 *normals);

private:
    float _xmin, _xmax;
    float _ymin, _ymax;
    float _zmin, _zmax;

    bool _dirty;
};

SK_END_NAMESPACE

#endif