#ifndef BALL_H
#define BALL_H

#include "gameobject.h"

class Ball : public GameObject
{
public:
    Ball();
    Ball(glm::vec2 pos, float radius, glm::vec2 velocity, 
        SK::Texture* text, SK::Shader* shdr);


    glm::vec2 move(float dt, unsigned int winWidth);
    void reset(glm::vec2 position, glm::vec2 velocity);
    bool isStuck() { return _stuck; }
    void setStuck(bool stuck) { _stuck = stuck; }
    float radius() { return _radius; }

private:
    float _radius;
    bool _stuck;
};

#endif
