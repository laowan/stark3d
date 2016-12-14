#include "ball.h"

Ball::Ball() : GameObject()
{
    this->radius = 10.0f;
    this->stuck = true;
}

Ball::Ball(glm::vec2 pos, float radius, glm::vec2 velocity, 
    SK::Texture* text, SK::Shader* shdr)
    : GameObject(pos, glm::vec2(radius*2, radius*2), glm::vec3(1.0), velocity, text, shdr)
{
    this->radius = radius;
    this->stuck = true;
}

