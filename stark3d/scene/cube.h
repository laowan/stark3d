#ifndef _CUBE_H
#define _CUBE_H

#include "node.h"

SK_BEGIN_NAMESPACE

class Cube : public SceneNode
{
public:
    Cube();
    Cube(double edgeLength);
    ~Cube();

    bool render();

private:
    uint32 _vb;
};

SK_END_NAMESPACE

#endif