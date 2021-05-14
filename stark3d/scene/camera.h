#pragma once

#include "global.h"

#include "utils/linmath.h"
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

    Viewport& getViewport() { return _viewport; }

    void getViewMat(mat4x4 mat);
    void getProjMat(mat4x4 mat);

    void setPerspective(float fov, float aspect, float n, float f);
    void setLookAt(vec3 eye, vec3 front, vec3 up);
    void getPosition(vec3 pos);
    void getFrontDir(vec3 front);

private:
    void getPerspectiveProjMat(mat4x4 mat);
    void getOrthographicProjMat(mat4x4 mat);
            
private:
    Viewport _viewport;
    mat4x4 _viewMat;
    mat4x4 _projMat;
    vec3 _eye;
    vec3 _front;
    vec3 _up;
    vec3 _right;
};

SK_END_NAMESPACE
