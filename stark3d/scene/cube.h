#ifndef _CUBE_H
#define _CUBE_H

#include "node.h"

SK_BEGIN_NAMESPACE

class STARK_API Cube : public SceneNode
{
public:
    Cube();
    Cube(double edgeLength);
    ~Cube();
    std::string type() { return "Cube"; }

    bool render(RenderAction* act);

private:
    uint32 _vb;
    uint32 _triCount;
};

SK_END_NAMESPACE

#endif