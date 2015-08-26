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

Point BBox::maxPoint() const
{
	return Point(_xmax, _ymax, _zmax);
}

Point BBox::minPoint() const
{
	return Point(_xmin, _ymin, _zmin);
}

std::vector<Point> BBox::points() const
{
	std::vector<Point> pts;

	pts.push_back(Point(_xmax, _ymax, _zmax));
	pts.push_back(Point(_xmax, _ymax, _zmin));

	pts.push_back(Point(_xmax, _ymax, _zmin));
	pts.push_back(Point(_xmax, _ymin, _zmin));

	pts.push_back(Point(_xmax, _ymin, _zmin));
	pts.push_back(Point(_xmax, _ymin, _zmax));

	pts.push_back(Point(_xmax, _ymin, _zmax));
	pts.push_back(Point(_xmax, _ymax, _zmax));

	pts.push_back(Point(_xmin, _ymax, _zmax));
	pts.push_back(Point(_xmin, _ymax, _zmin));

	pts.push_back(Point(_xmin, _ymax, _zmin));
	pts.push_back(Point(_xmin, _ymin, _zmin));

	pts.push_back(Point(_xmin, _ymin, _zmin));
	pts.push_back(Point(_xmin, _ymin, _zmax));

	pts.push_back(Point(_xmin, _ymin, _zmax));
	pts.push_back(Point(_xmin, _ymax, _zmax));

	pts.push_back(Point(_xmax, _ymax, _zmax));
	pts.push_back(Point(_xmin, _ymax, _zmax));

	pts.push_back(Point(_xmax, _ymax, _zmin));
	pts.push_back(Point(_xmin, _ymax, _zmin));

	pts.push_back(Point(_xmax, _ymin, _zmax));
	pts.push_back(Point(_xmin, _ymin, _zmax));

	pts.push_back(Point(_xmax, _ymin, _zmin));
	pts.push_back(Point(_xmin, _ymin, _zmin));

	return pts;
}

SK_END_NAMESPACE