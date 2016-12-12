#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "base.h"

class GameObject
{
public:
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 sz, 
        glm::vec3 col = glm::vec3(1.0f), 
        glm::vec2 vel = glm::vec2(0.0f, 0.0f));

    virtual void draw();

public:
    glm::vec2 position, size, velocity;
    glm::vec3 color;
    float rotation;
    bool isSolid;
    bool destoryed;
};

#endif
