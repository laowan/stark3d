#include "camera.h"
#include "scene/scene.h"
#include "scene/renderer.h"
#include "string.h"

SK_BEGIN_NAMESPACE

Camera::Camera()
{}

Camera::~Camera()
{}

void Camera::render(Scene* scene)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glDepthMask(GL_FALSE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    std::vector<Renderer*>& renderers = scene->getRenderer();
    for (auto renderer : renderers)
    {
        renderer->render(this, scene);
    }
}

const Matrix4& Camera::getViewMatrix()
{
    return _viewMat;
}

const Matrix4& Camera::getProjectMatrix()
{
    return _projMat;
}

SK_END_NAMESPACE
