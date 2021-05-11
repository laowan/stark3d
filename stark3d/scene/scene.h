#pragma once

#include "global.h"
#include "scene/entity.h"
#include <vector>

SK_BEGIN_NAMESPACE

class Scene
{
public:
    Scene();
    ~Scene();

    Entity* createEntity(const std::string& name);
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    bool loadGLTF(const std::string& path);

private:
    std::vector<Entity*> _entities;
};

SK_END_NAMESPACE