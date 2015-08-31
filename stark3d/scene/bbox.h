#ifndef _BBOX_H
#define _BBOX_H

#include "global.h"
#include "renderaction.h"
#include <vector>

#define BBOX_LIMIT 1.0e+12

SK_BEGIN_NAMESPACE

struct Point2
{
	Point2() : x(0.0), y(0.0) {}
	Point2(float x, float y) { this->x = x; this->y = y; }
	float x, y;
};

struct Point3
{
	Point3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	float x, y, z;
};

struct Point
{
	Point(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	float x, y, z;
};

class BBox
{
public:
    BBox();
    void add(float x, float y, float z);
    bool render(RenderAction* act);
	Point maxPoint() const;
	Point minPoint() const;
	std::vector<Point> points() const;

private:
    float _xmin, _xmax;
    float _ymin, _ymax;
    float _zmin, _zmax;

    bool _dirty;
};

SK_END_NAMESPACE

#endif