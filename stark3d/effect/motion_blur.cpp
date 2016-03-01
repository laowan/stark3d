#include "effect.h"
#include "module.h"

SK_BEGIN_NAMESPACE

EffectMotionBlur::EffectMotionBlur() : _vb(0), _rb1(0), _rb2(0)
{
    float vertexData[] = {
        -1.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
         1.0, -1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
         1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
                         
         1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
        -1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,
        -1.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, };

    _vb = Module::renderDev().createVertexBuffer(sizeof(vertexData), vertexData);
}

EffectMotionBlur::~EffectMotionBlur()
{
    if (_vb)
    {
        Module::renderDev().destroyBuffer(_vb);
        _vb = 0;
    }

    if (_rb1)
    {
        Module::renderDev().destroyRenderBuffer(_rb1);
    }

    if (_rb2)
    {
        Module::renderDev().destroyRenderBuffer(_rb2);
    }
}

/*!
    1. render the scene to a texture.
    2. map the texture to the screen.
*/
void EffectMotionBlur::render()
{
    static bool pass = false;
    pass = !pass;

    int width = Module::sceneMan().getCamera()->getViewport().pixWidth;
    int height = Module::sceneMan().getCamera()->getViewport().pixHeight;

    uint32* rb;
    if (pass)
        rb = &_rb2;
    else
        rb = &_rb1;

    if (*rb == 0)
        *rb = Module::renderDev().createRenderBuffer((uint32)width, (uint32)height);

    /*
    draw something
    */
    Module::renderDev().setRenderBuffer(*rb);

    //gsCam->getViewport().resize(width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Module::shaderMan().use("normal");

    ShaderUniforms& uniforms = Module::shaderMan().currentShader()->uniforms();

    // calculate the mvp matrix and apply it to the shader
    uniforms.mvp = Module::sceneMan().getCamera()->getViewProjMat();
    uniforms.color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    uniforms.lightPosition = glm::vec3(300.0f, 300.0f, 300.0f);
    uniforms.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    uniforms.activeTexture = 0;

    Module::shaderMan().currentShader()->commitUniforms();

    // now render the scene
    Module::sceneMan().render();

    Module::renderDev().setRenderBuffer(0);

    if (_rb1 <= 0 || _rb2 <= 0) return;

    /*
        add two textures
    */
    uint32 texture1 = Module::renderDev().getRenderBufferTexture(_rb1);
    uint32 texture2 = Module::renderDev().getRenderBufferTexture(_rb2);

    if (!pass)
    {
        uint32 tmp = texture1;
        texture1 = texture2;
        texture2 = tmp;
    }

    Module::shaderMan().use("screen_effects/motion_blur");
    ShaderUniforms& u = Module::shaderMan().currentShader()->uniforms();
    u.activeTexture = 0;
    u.activeTexture2 = 1;
    Module::shaderMan().currentShader()->commitUniforms();

    Module::renderDev().setVertexBuffer(_vb);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    uint32 stride(sizeof(float)* 3 + sizeof(float)* 3 + sizeof(float)* 2);
    Module::renderDev().setVertexLayout(0, stride, 0);
    Module::renderDev().setVertexLayout(1, stride, (const void*)(3 * sizeof(float)));
    Module::renderDev().setVertexLayout(2, stride, (const void*)(6 * sizeof(float)));
    Module::renderDev().draw(SK::PRIM_TRIANGLES, 0, 6);

    Module::renderDev().setVertexBuffer(0);
}

SK_END_NAMESPACE
