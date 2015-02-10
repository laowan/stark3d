#include "transform.h"
#include "utils/matrix.h"

SK_BEGIN_NAMESPACE

Transform::Transform()
{
    _matrix = new Matrix();
}

Transform::~Transform()
{
    if (_matrix)
        delete _matrix;
}

bool Transform::render(RenderAction* act)
{
    // modify the model matrix
    act->_modelMat = act->_modelMat.mul(*_matrix);
    return true;
}

SK_END_NAMESPACE
