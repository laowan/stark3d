#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "node.h"

SK_BEGIN_NAMESPACE

class Matrix;
class Transform : public SceneNode
{
public:
    Transform();
    ~Transform();
    std::string type() { return "Transform"; }

    bool renderEnter(RenderAction* act);
    bool render(RenderAction* act);
    bool renderLeave(RenderAction* act);

    Matrix& matrix() { return *_matrix; }
private:
    Matrix* _matrix;
};

SK_END_NAMESPACE

#endif