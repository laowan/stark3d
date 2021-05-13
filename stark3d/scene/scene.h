#pragma once

#include "global.h"
#include "scene/entity.h"
#include <vector>

SK_BEGIN_NAMESPACE

class Mesh;
class Scene
{
public:
    Scene();
    ~Scene();

    Entity* createEntity(const std::string& name);
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    void addMesh(Mesh* mesh) { _meshes.push_back(mesh); }

    bool loadGLTF(const std::string& path);

private:

private:
    std::vector<Entity*> _entities;
    std::vector<Mesh*> _meshes;
};

SK_END_NAMESPACE