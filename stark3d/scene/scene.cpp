#include "scene/scene.h"

SK_BEGIN_NAMESPACE

Scene::Scene()
{

}

Scene::~Scene()
{

}

Entity* Scene::createEntity(const std::string& name)
{
    Entity* ent = new Entity(name);
    return ent;
}

void Scene::addEntity(Entity* entity)
{
    _entities.push_back(entity);
}

void Scene::removeEntity(Entity* entity)
{
    auto it = std::find(_entities.begin(), _entities.end(), entity);
    if (it != _entities.end())
        _entities.erase(it);
}

bool Scene::loadGLTF(const std::string& path)
{
    return false;
}

SK_END_NAMESPACE