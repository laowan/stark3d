#pragma once

#include "global.h"
#include <vector>

SK_BEGIN_NAMESPACE

class Component;
class Entity
{
public:
    template <class T>
    T* addComponent();
    template <class T>
    T* getComponent() const;
private:
    std::vector<Component*> _components;
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
    for (Component* i : _addedComponents)
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