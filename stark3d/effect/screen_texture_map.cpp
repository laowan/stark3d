#include "effect.h"
#include "module.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

SK_BEGIN_NAMESPACE

EffectTextureMap::EffectTextureMap() : _vb(0), _rb(0)
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

EffectTextureMap::~EffectTextureMap()
{
    if (_vb)
    {
        Module::renderDev().destroyBuffer(_vb);
        _vb = 0;
    }

    if (_rb)
    {
        Module::renderDev().destroyRenderBuffer(_rb);
    }
}

/*!
    1. render the scene to a texture.
    2. map the texture to the screen.
*/
void EffectTextureMap::render()
{
    int width = Module::sceneMan().getCamera()->getViewport().pixWidth;
    int height = Module::sceneMan().getCamera()->getViewport().pixHeight;

    if (!_rb)
    {
        _rb = Module::renderDev().createRenderBuffer((uint32)width, (uint32)height);
    }

    /*
    draw something
    */
    Module::renderDev().setRenderBuffer(_rb);

    //gsCam->getViewport().resize(width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Module::resMan().useShader("normal");

    ShaderUniforms& uniforms = Module::resMan().currentShader()->uniforms();

    // calculate the mvp matrix and apply it to the shader
    uniforms.mvp = Module::sceneMan().getCamera()->getViewProjMat();
    uniforms.color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    uniforms.lightPosition = glm::vec3(300.0f, 300.0f, 300.0f);
    uniforms.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    uniforms.activeTexture = 0;

    Module::resMan().currentShader()->commitUniforms();

    // now render the scene
    Module::sceneMan().render();

    Module::renderDev().setRenderBuffer(0);

//     if (0)
//     {
//         glBindTexture(GL_TEXTURE_2D, colortexture);
//         unsigned char* pdata = (unsigned char*)malloc(sizeof(unsigned char)* 4 * width * height);
//         memset(pdata, 0, sizeof(char)* 3 * width * height);
//         glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pdata);
//         glBindTexture(GL_TEXTURE_2D, 0);
// 
//         stbi_write_bmp("111.bmp", width, height, 4, pdata);
//         free(pdata);
//     }
    
    Module::resMan().useShader("screen_effects/texture_map");
    ShaderUniforms& u = Module::resMan().currentShader()->uniforms();
    u.activeTexture = 0;
    u.filter[0].x = 0.299; u.filter[1].x = 0.587; u.filter[2].x = 0.184; u.filter[3].x = 0.0;
    u.filter[0].y = 0.299; u.filter[1].y = 0.587; u.filter[2].y = 0.184; u.filter[3].y = 0.0;
    u.filter[0].z = 0.299; u.filter[1].z = 0.587; u.filter[2].z = 0.184; u.filter[3].z = 0.0;
    u.filter[0].w = 0.0;   u.filter[1].w = 0.0;   u.filter[2].w = 0.0;   u.filter[3].w = 1.0;
    u.viewportWidth = width;
    u.viewportHeight = height;
    Module::resMan().currentShader()->commitUniforms();

    Module::renderDev().setVertexBuffer(_vb);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Module::renderDev().getRenderBufferTexture(_rb));

    uint32 stride(sizeof(float)* 3 + sizeof(float)* 3 + sizeof(float)* 2);
    Module::renderDev().setVertexLayout(0, stride, 0);
    Module::renderDev().setVertexLayout(1, stride, (const void*)(3 * sizeof(float)));
    Module::renderDev().setVertexLayout(2, stride, (const void*)(6 * sizeof(float)));
    Module::renderDev().draw(SK::PRIM_TRIANGLES, 0, 6);

    Module::renderDev().setVertexBuffer(0);
}

SK_END_NAMESPACE
