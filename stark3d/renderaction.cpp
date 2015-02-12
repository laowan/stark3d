#include "renderaction.h"

SK_BEGIN_NAMESPACE

void RenderAction::reset()
{
    _modelMat = Matrix();
    _color = glm::vec4(1.0, 0.0, 0.0, 1.0);
    _activeTexture = 0;
}

SK_END_NAMESPACE
