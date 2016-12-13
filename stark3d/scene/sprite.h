#ifndef _SPRITE_H
#define _SPRITE_H

#include "node.h"
#include "texture.h"
#include "utils/shader.h"

SK_BEGIN_NAMESPACE

class STARK_API Sprite : public SceneNode
{
public:
    Sprite();
    ~Sprite();

    void draw(Shader* shader, Texture* texture, glm::vec2 position,
            glm::vec2 size = glm::vec2(10, 10), 
            float rotate = 0.0f, 
            glm::vec3 color = glm::vec3(1.0f));
private:
    void init();

private:
    SK_DECLARE_IMPL(Sprite);
};

SK_END_NAMESPACE

#endif
