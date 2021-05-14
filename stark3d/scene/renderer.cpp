#include "scene/renderer.h"
#include "scene/camera.h"

SK_BEGIN_NAMESPACE

void Renderer::render(Camera* camera)
{
    Material* mat = getMaterial();
    render(camera, mat);
}

void Renderer::render(Camera* camera, Material* mat)
{

}

SK_END_NAMESPACE