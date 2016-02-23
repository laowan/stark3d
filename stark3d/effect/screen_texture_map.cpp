#include "effect.h"
#include "module.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

SK_BEGIN_NAMESPACE

Texture* txt = NULL; 
GLuint fbo, colortexture, depthtexture;

EffectTextureMap::EffectTextureMap() : _vb(0)
{
    float vertexData[] = {
        -1.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
         1.0, -1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
         1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
                         
         1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
        -1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,
        -1.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, };

    _vb = Module::renderDev().createVertexBuffer(sizeof(vertexData), vertexData);
    txt = new Texture;

    glGenFramebuffers(1, &fbo);
    glGenTextures(1, &colortexture);
    glGenTextures(1, &depthtexture);
}

EffectTextureMap::~EffectTextureMap()
{
    if (_vb)
    {
        Module::renderDev().destroyBuffer(_vb);
        _vb = 0;
    }

    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &colortexture);
    glDeleteTextures(1, &depthtexture);
}

/*!
    1. render the scene to a texture.
    2. map the texture to the screen.
*/
void EffectTextureMap::render()
{
    int width = Module::sceneMan().getCamera()->getViewport().pixWidth;
    int height = Module::sceneMan().getCamera()->getViewport().pixHeight;

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glBindTexture(GL_TEXTURE_2D, colortexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colortexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colortexture, 0);

    glBindTexture(GL_TEXTURE_2D, depthtexture);
    //glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthtexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthtexture, 0);


    static const GLenum draw_buffer[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, draw_buffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    /*
    draw something
    */
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (0)
    {
        glBindTexture(GL_TEXTURE_2D, colortexture);
        unsigned char* pdata = (unsigned char*)malloc(sizeof(unsigned char)* 4 * width * height);
        memset(pdata, 0, sizeof(char)* 3 * width * height);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pdata);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_write_bmp("111.bmp", width, height, 4, pdata);
        free(pdata);
    }
    

//     glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//     glClearDepth(1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //txt->render(NULL);
    
    Module::shaderMan().use("screen_effects/texture_map");
    ShaderUniforms& u = Module::shaderMan().currentShader()->uniforms();
    u.activeTexture = 0;
    Module::shaderMan().currentShader()->commitUniforms();

    Module::renderDev().setVertexBuffer(_vb);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colortexture);

    uint32 stride(sizeof(float)* 3 + sizeof(float)* 3 + sizeof(float)* 2);
    Module::renderDev().setVertexLayout(0, stride, 0);
    Module::renderDev().setVertexLayout(1, stride, (const void*)(3 * sizeof(float)));
    Module::renderDev().setVertexLayout(2, stride, (const void*)(6 * sizeof(float)));
    Module::renderDev().draw(SK::PRIM_TRIANGLES, 0, 6);

    Module::renderDev().setVertexBuffer(0);

}

SK_END_NAMESPACE
