#include "bbox.h"
#include <vector>
using std::vector;

SK_BEGIN_NAMESPACE

BBox::BBox() : _dirty(true)
{
    _xmin = _ymin = _zmin = (float)BBOX_LIMIT;
    _xmax = _ymax = _zmax = (float)-BBOX_LIMIT;
}

void BBox::add(float x, float y, float z)
{
    _xmin = _xmin < x ? _xmin : x;
    _ymin = _ymin < y ? _ymin : y;
    _zmin = _zmin < z ? _zmin : z;

    _xmax = _xmax > x ? _xmax : x;
    _ymax = _ymax > y ? _ymax : y;
    _zmax = _zmax > z ? _zmax : z;

    _dirty = true;
}

bool BBox::render(RenderAction* act)
{
    if (_dirty)
    {
        _dirty = false;
    }
    return true;
}

Point3 BBox::maxPoint() const
{
    return Point3(_xmax, _ymax, _zmax);
}

Point3 BBox::minPoint() const
{
    return Point3(_xmin, _ymin, _zmin);
}

std::vector<Point3> BBox::points() const
{
    std::vector<Point3> pts;

    // 12 edges
    pts.push_back(Point3(_xmax, _ymax, _zmax));
    pts.push_back(Point3(_xmax, _ymax, _zmin));

    pts.push_back(Point3(_xmax, _ymax, _zmin));
    pts.push_back(Point3(_xmax, _ymin, _zmin));

    pts.push_back(Point3(_xmax, _ymin, _zmin));
    pts.push_back(Point3(_xmax, _ymin, _zmax));

    pts.push_back(Point3(_xmax, _ymin, _zmax));
    pts.push_back(Point3(_xmax, _ymax, _zmax));

    pts.push_back(Point3(_xmin, _ymax, _zmax));
    pts.push_back(Point3(_xmin, _ymax, _zmin));

    pts.push_back(Point3(_xmin, _ymax, _zmin));
    pts.push_back(Point3(_xmin, _ymin, _zmin));

    pts.push_back(Point3(_xmin, _ymin, _zmin));
    pts.push_back(Point3(_xmin, _ymin, _zmax));

    pts.push_back(Point3(_xmin, _ymin, _zmax));
    pts.push_back(Point3(_xmin, _ymax, _zmax));

    pts.push_back(Point3(_xmax, _ymax, _zmax));
    pts.push_back(Point3(_xmin, _ymax, _zmax));

    pts.push_back(Point3(_xmax, _ymax, _zmin));
    pts.push_back(Point3(_xmin, _ymax, _zmin));

    pts.push_back(Point3(_xmax, _ymin, _zmax));
    pts.push_back(Point3(_xmin, _ymin, _zmax));

    pts.push_back(Point3(_xmax, _ymin, _zmin));
    pts.push_back(Point3(_xmin, _ymin, _zmin));

    return pts;
}

void BBox::getSixPlanes(Point3 *pnts, Point3 *normals)
{
    pnts[0] = maxPoint();
    normals[0] = Point3(1.0, 0.0, 0.0);

    pnts[1] = maxPoint();
    normals[1] = Point3(0.0, 1.0, 0.0);

    pnts[2] = maxPoint();
    normals[2] = Point3(0.0, 0.0, 1.0);

    pnts[3] = minPoint();
    normals[3] = Point3(-1.0, 0.0, 0.0);

    pnts[4] = minPoint();
    normals[4] = Point3(0.0, -1.0, 0.0);

    pnts[5] = minPoint();
    normals[5] = Point3(0.0, 0.0, -1.0);
}

SK_END_NAMESPACE