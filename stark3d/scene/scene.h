#pragma once

#include "global.h"
#include "scene/entity.h"
#include <vector>

SK_BEGIN_NAMESPACE

class Mesh;
class Renderer;
class Camera;
class Material;
class Texture;
class Scene
{
public:
    Scene();
    ~Scene();

    Entity* createEntity(const std::string& name);
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    int addMesh(Mesh* mesh);
    Mesh* getMesh(int n);

    int addMaterial(Material* material);
    Material* getMaterial(int n);

    int addTexture(Texture* texture);
    Texture* getTexture(int n);

    int addRenderer(Renderer* renderer);

    std::vector<Renderer*>& getRenderer() { return _renderers; }
    Camera* getCamera() { return _camera; }

    bool loadGLTF(const std::string& path);

    void update();
    void render();

    void dump();

private:
    std::vector<Entity*> _entities;
    std::vector<Mesh*> _meshes;
    std::vector<Material*> _materials;
    std::vector<Renderer*> _renderers;
    std::vector<Texture*> _textures;
    Camera* _camera;
};

SK_END_NAMESPACE