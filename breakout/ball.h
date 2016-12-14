#ifndef BALL_H
#define BALL_H

#include "gameobject.h"

class Ball : public GameObject
{
public:
    Ball();
    Ball(glm::vec2 pos, float radius, glm::vec2 velocity, 
        SK::Texture* text, SK::Shader* shdr);

private:
    float radius;
    bool stuck;
};

#endif
