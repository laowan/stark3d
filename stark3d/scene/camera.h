#ifndef _CAMERA_H
#define _CAMERA_H

#include "node.h"
#include "utils/matrix.h"
#include <glload/gl_3_3.h>

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

		pixScale = pixHeight / extent;

        glViewport(0, 0, width, height);
    }

public:
    double extent;
    int pixWidth;
    int pixHeight;
    double pixScale; // screen pixel per unit in clip space
};

class Camera : public SceneNode
{
public:
    Camera();
    ~Camera();

    Viewport& getViewport() { return _viewport; }
    Matrix& getViewMatrix() { return _viewMat; }
    glm::mat4 getViewMat();
    glm::mat4 getViewProjMat();

    void reset();
	void zoomAll(const BBox& bbox);

private:
    glm::mat4 getPerspectiveProjMat();
    glm::mat4 getOrthographicProjMat();
            
private:
    Viewport _viewport;
    Matrix _viewMat; // view to world
};

SK_END_NAMESPACE

#endif
