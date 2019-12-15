#ifndef SK_CAMERA_H
#define SK_CAMERA_H

#include "global.h"

#include "utils/linmath.h"
#include "utils/gldefine.h"

SK_BEGIN_NAMESPACE

class Viewport
{
public:
    Viewport() : extent(10.0f) {}
    ~Viewport() {}

    void resize(int width, int height)
    {
        pixWidth = width;
        pixHeight = height;

        extent = pixWidth;
        pixScale = pixHeight / extent;

        glViewport(0, 0, width, height);
    }

public:
    double extent;
    int pixWidth;
    int pixHeight;
    double pixScale; // screen pixel per unit in clip space
};

class Camera
{
public:
    Camera();
    ~Camera();

    Viewport& getViewport() { return _viewport; }
    //Matrix& getViewMatrix() { return _viewMat; }
    //glm::mat4 getViewMat();
    //glm::mat4 getViewProjMat();
    void getViewMat(mat4x4 mat);

    void reset();

private:
    //glm::mat4 getPerspectiveProjMat();
    //glm::mat4 getOrthographicProjMat();
            
private:
    Viewport _viewport;
    //Matrix _viewMat; // view to world
};

SK_END_NAMESPACE

#endif
