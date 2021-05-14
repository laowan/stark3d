#ifndef _RENDERACTION_H
#define _RENDERACTION_H

#include "utils/matrix.h"
#include <glm/gtc/type_ptr.hpp>

#include <stack>

SK_BEGIN_NAMESPACE

/*!
    We use this class to keep the state used during render procedure.
    The behavior is just like a global variable. e.g. model matrix.
*/
class RenderAction
{
public:
    void reset();

public:
    std::stack<Matrix> _modelMatStack;
    Matrix _modelMat;
    glm::vec4 _color;
    uint32 _activeTexture;
};

SK_END_NAMESPACE

#endif
