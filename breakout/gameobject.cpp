#include "gameobject.h"

GameObject::GameObject()
    : position(0,0), size(1,1), velocity(0.0f), color(1.0f),
      rotation(0.0f), isSolid(false),
      texture(NULL), shader(NULL)
{
    destoryed = false;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 sz,
    glm::vec3 col, glm::vec2 vel,
    SK::Texture *txt, 
    SK::Shader *shdr)
    : position(pos), size(sz), 
      color(col), velocity(vel),
      texture(txt), shader(shdr)
{
    isSolid = false;
    destoryed = false;
}

void GameObject::setShader(SK::Shader *shader)
{
    this->shader = shader;
}

void GameObject::setTexture(SK::Texture *texture)
{
    this->texture = texture;
}

void GameObject::setVelocity(glm::vec2 vel)
{
    this->velocity = vel;
}

void GameObject::draw(SK::Sprite *sprite)
{
    if (!shader || !texture) return;
    sprite->draw(shader, texture, position, size, 0.0, color);
}