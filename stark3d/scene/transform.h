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
    Transform() : _isMatrix(true) {}
    ~Transform() {}

    void setMatrix(const Matrix4& mat) { _isMatrix = true; _matrix = mat; }

private:
    Transform* _parent;
    std::vector<Transform*> _children;

    bool _isMatrix;
    Vector3 _position;
    Quaternion _rotation;
    Vector3 _scale;
    Matrix4 _matrix;
};

SK_END_NAMESPACE
