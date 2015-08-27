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

bool Transform::renderEnter(RenderAction* act)
{
    act->_modelMatStack.push(act->_modelMat);

    Matrix mat = act->_modelMat.mul(*_matrix);
    act->_modelMatStack.push(mat);

    // modify the model matrix
    act->_modelMat = act->_modelMatStack.top();
    return true;
}

bool Transform::render(RenderAction* act)
{
    // modify the model matrix
    //act->_modelMat = act->_modelMat.mul(*_matrix);
    //act->_modelMat = act->_modelMatStack.top();
    return true;
}

bool Transform::renderLeave(RenderAction* act)
{
    act->_modelMatStack.pop();

    act->_modelMat = act->_modelMatStack.top();
    act->_modelMatStack.pop();

    return true;
}

SK_END_NAMESPACE
