#pragma once

#include "global.h"
#include "scene/component.h"

SK_BEGIN_NAMESPACE

class Camera;
class Material;
class Component;
class Renderer : public Component
{
public:
    virtual void render(Camera* camera);
    virtual void render(Camera* camera, Material* mat);

    Material* getMaterial() { return _material; }

private:
    Material* _material;
};

SK_END_NAMESPACE