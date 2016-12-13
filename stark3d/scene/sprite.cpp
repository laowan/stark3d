#include "sprite.h"
#include "module.h"

SK_BEGIN_NAMESPACE

class SpriteImpl : public Impl<Sprite>
{
public:
    void init();
    void exit();

    uint32 quadVAO;
    uint32 quadVBO;
};

void SpriteImpl::init()
{
    // Configure VAO/VBO
    GLfloat vertices[] = {
        // Pos            // Tex
        0.0f, 1.0f, -30.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -30.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -30.0f, 0.0f, 0.0f,

        0.0f, 1.0f, -30.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -30.0f, 1.0f, 1.0f,
        1.0f, 0.0f, -30.0f, 1.0f, 0.0f
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

void Sprite::draw(Shader* shader, Texture* texture, glm::vec2 position, glm::vec2 size, 
                 float rotate, glm::vec3 color)
{
    SK_D(Sprite);

    glDisable(GL_DEPTH_TEST);

    // Prepare transformations
    shader->use();
    //glm::mat4 model;
    //model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    //model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    //shader.SetMatrix4("model", model);

    // Render textured quad
    //shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture->bind(); 
    
    ShaderUniforms& uniforms = shader->uniforms();
    uniforms.color = glm::vec4(color, 1.0);
    uniforms.activeTexture = 0;
    uniforms.mvp = Module::sceneMan().getCamera()->getViewProjMat();
    shader->commitUniforms();

    glBindBuffer(GL_ARRAY_BUFFER, d->quadVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindVertexArray(d->quadVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //glBindVertexArray(0);
}

void Sprite::init()
{
   
}

SK_END_NAMESPACE
