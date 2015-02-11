#ifndef _CAMERA_H
#define _CAMERA_H

#include "node.h"
#include "utils/matrix.h"
#include <glload/gl_3_3.h>

SK_BEGIN_NAMESPACE

class Viewport
{
public:
    Viewport() : _extent(200.0f) {}
    ~Viewport() {}

    void resize(int width, int height)
    {
        _pixWidth = width;
        _pixHeight = height;

        if (_pixHeight > _pixWidth)
        {
            _hpixScale = _pixWidth / _extent;
            _vpixScale = _hpixScale;
        }
        else
        {
            _vpixScale = _pixHeight / _extent;
            _hpixScale = _vpixScale;
        }

        glViewport(0, 0, width, height);
    }

public:
    double _extent;
    int _pixWidth;
    int _pixHeight;
    double _hpixScale; // screen pixel per unit in clip space
    double _vpixScale;
};

class Camera : public SceneNode
{
public:
    Camera();
    ~Camera();

    Viewport& getViewport() { return _viewport; }
    Matrix& getViewMat() { return _viewMat; }
    glm::mat4 getViewProjMat();

    void reset();

private:
    glm::mat4 getPerspectiveProjMat();
    glm::mat4 getOrthographicProjMat();
            
private:
    Viewport _viewport;
    Matrix _viewMat; // view to world
};

SK_END_NAMESPACE

#endif
