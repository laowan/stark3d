#pragma once

#include "global.h"
#include "scene/object.h"
#include "scene/transform.h"
#include <vector>

SK_BEGIN_NAMESPACE

class Component;
class Entity : public Object
{
public:
    Entity(const std::string& name = "");
    ~Entity();

    Transform* getTransform() { return _transform; }

    template <class T>
    T* addComponent();

    template <class T>
    T* getComponent() const;

private:
    void addComponent(Component* com);

private:
    std::vector<Component*> _components;
    Transform* _transform;
};

template <class T>
T* Entity::addComponent()
{
    T* com = new T();
    this->addComponent(com);
    return com;
}

template <class T>
T* Entity::getComponent() const
{
    for (Component* i : _components)
    {
        T* com = dynamic_cast<T*>(i);
        if (com)
        {
            return com;
        }
    }
    return nullptr;
}

SK_END_NAMESPACE