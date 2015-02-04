#ifndef _CUBE_H
#define _CUBE_H

#include "node.h"

namespace Scene {

class Cube : public SceneNode
{
public:
    Cube();
    ~Cube();

    bool render();

private:
    int _vb;
};

}

#endif