#include "sprite.h"
#include "module.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

SK_BEGIN_NAMESPACE

class SpriteImpl : public Impl<Sprite>
{
public:
    void init();
    void exit();

    uint32 quadVAO;
    uint32 quadVBO;
    SK::Cube *cube;
};

void SpriteImpl::init()
{
    cube = new SK::Cube;

    // Configure VAO/VBO
    GLfloat vertices[] = {
        // Pos             // Normal         // Tex
        0.0f, 1.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, -0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, -0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    //glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindVertexArray(quadVAO);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    //
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
}

void SpriteImpl::exit()
{
    glDeleteVertexArrays(1, &quadVAO);

    delete cube;
}

Sprite::Sprite()
{
    SK_I(Sprite);
    d->init();
}

Sprite::~Sprite()
{
    SK_E(Sprite);
    d->exit();
}

/*
    Draw the sprite by the given parameters.
    \param shader
    \param texture
    \param position  screen coordinates(pixel), upper-left is origin
    \param size      screen pixel
    \param rotate
    \param color
*/
void Sprite::draw(Shader* shader, Texture* texture, glm::vec2 position, glm::vec2 size, 
                 float rotate, glm::vec3 color)
{
    SK_D(Sprite);

    //glDisable(GL_DEPTH_TEST);

    shader->use();

    Camera* cam = Module::sceneMan().getCamera();
    int width = cam->getViewport().pixWidth;
    int height = cam->getViewport().pixHeight;

    glm::mat4 model;
    position.x -= (float)width / 2;
    position.y = (float)height / 2 - position.y - size.y;
    model = glm::translate(model, glm::vec3(position, 0.0f));  
    model = glm::scale(model, glm::vec3(size, 1.0f));

    glm::mat4 mvp = cam->getViewProjMat();
    mvp *= model;

    glActiveTexture(GL_TEXTURE0);
    texture->bind(); 
    
    ShaderUniforms& uniforms = shader->uniforms();
    uniforms.color = glm::vec4(color, 1.0);
    uniforms.activeTexture = 0;
    uniforms.mvp = mvp;
    shader->commitUniforms();

    //d->cube->render();
    uint32 stride(sizeof(float)*3 + sizeof(float)*3 + sizeof(float)*2);

    glBindBuffer(GL_ARRAY_BUFFER, d->quadVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (const void*)(3*sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (const void*)(6*sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(2);

    //glBindVertexArray(d->quadVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //glBindVertexArray(0);
}

void Sprite::init()
{
   
}

SK_END_NAMESPACE
