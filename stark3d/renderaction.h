#ifndef _RENDERACTION_H
#define _RENDERACTION_H

#include "utils/matrix.h"
#include <glm/gtc/type_ptr.hpp>

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
    Matrix _modelMat;
    glm::vec4 _color;
};

SK_END_NAMESPACE

#endif
