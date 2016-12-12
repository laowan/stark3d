#include "gameobject.h"

GameObject::GameObject()
    : position(0,0), size(1,1), velocity(0.0f), color(1.0f),
      rotation(0.0f), isSolid(false), destoryed(false)
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 sz, glm::vec3 col, glm::vec2 vel)
    : position(pos), size(sz), color(col), velocity(vel)
{
}

void GameObject::draw()
{
}