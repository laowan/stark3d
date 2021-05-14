#pragma once

#include "global.h"
#include "scene/entity.h"
#include <vector>

SK_BEGIN_NAMESPACE

class Mesh;
class Renderer;
class Camera;
class Scene
{
public:
    Scene();
    ~Scene();

    Entity* createEntity(const std::string& name);
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    void addMesh(Mesh* mesh) { _meshes.push_back(mesh); }
    void addRenderer(Renderer* renderer) { _renderers.push_back(renderer); }

    std::vector<Renderer*>& getRenderer() { return _renderers; }

    bool loadGLTF(const std::string& path);

    void update();
    void render();

    void dump();

private:

private:
    std::vector<Entity*> _entities;
    std::vector<Mesh*> _meshes;
    std::vector<Renderer*> _renderers;
    Camera* _camera;
};

SK_END_NAMESPACE