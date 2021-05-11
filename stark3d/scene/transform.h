#pragma once

#include "global.h"
#include "scene/component.h"
#include "utils/math.h"
#include <vector>

SK_BEGIN_NAMESPACE

class Matrix;
class Transform : public Component
{
public:
    Transform();
    ~Transform();
private:
    Transform* _parent;
    std::vector<Transform*> _children;

    Vector3 _position;
    Quaternion _rotation;
    Vector3 _scale;
};

SK_END_NAMESPACE
