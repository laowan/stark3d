#pragma once

#include "global.h"

#include "utils/math.h"
#include "utils/gldefine.h"
#include "component.h"

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

class Component;
class Scene;
class Camera : public Component
{
public:
    Camera();
    ~Camera();

    void render(Scene* scene);

    void setViewMatrix(const Matrix4& mat) { _viewMat = mat; }

    const Matrix4& getViewMatrix();
    const Matrix4& getProjectMatrix();

private:
    Matrix4 _viewMat;
    Matrix4 _projMat;
};

SK_END_NAMESPACE
