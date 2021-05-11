#include "scene/entity.h"

SK_BEGIN_NAMESPACE

Entity::Entity(const std::string& name)
{
    _name = name;
    _transform = addComponent<Transform>();
}

Entity::~Entity()
{

}

void Entity::addComponent(Component* com)
{
    _components.push_back(com);
}

SK_END_NAMESPACE