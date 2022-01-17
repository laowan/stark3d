#include "ball.h"

Ball::Ball() : GameObject()
{
    _radius = 10.0f;
    _stuck = true;
}

Ball::Ball(glm::vec2 pos, float radius, glm::vec2 velocity, 
    SK::Texture* text, SK::Shader* shdr)
    : GameObject(pos, glm::vec2(radius*2, radius*2), glm::vec3(1.0), velocity, text, shdr)
{
    _radius = radius;
    _stuck = true;
}

glm::vec2 Ball::move(float dt, unsigned int winWidth)
{
    if (_stuck == false)
    {
        position += velocity * dt;
        if (position.x <= 0.0f)
        {
            velocity.x = -velocity.x;
            position.x = 0.0f;
        }
        else if (position.x >= winWidth - size.x)
        {
            velocity.x = -velocity.x;
            position.x = winWidth - size.x;
        }
        
        if (position.y <= 0)
        {
            velocity.y = -velocity.y;
            position.y = 0.0f;
        }
        
    }
    return this->position;
}

void Ball::reset(glm::vec2 position, glm::vec2 velocity)
{

}
