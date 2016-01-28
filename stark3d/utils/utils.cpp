#include "utils.h"
#include "../module.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace SK;

void skScreenshot(const char* file)
{
    int width = Module::sceneMan().getCamera()->getViewport().pixWidth;
    int height = Module::sceneMan().getCamera()->getViewport().pixHeight;

    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GLuint colortexture;
    glGenTextures(1, &colortexture);
    glBindTexture(GL_TEXTURE_2D, colortexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colortexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colortexture, 0);

    GLuint depthtexture;
    glGenTextures(1, &depthtexture);
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

    /*
    generate the image
    */
    glBindTexture(GL_TEXTURE_2D, colortexture);
    unsigned char* pdata = (unsigned char*)malloc(sizeof(unsigned char)* 4 * width * height);
    memset(pdata, 0, sizeof(char)* 3 * width * height);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pdata);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_write_bmp(file, width, height, 4, pdata);
    free(pdata);
}

void skCreateScene()
{
    // add three coordinate axes
    Line* axisX = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(500.0, 0.0, 0.0));
    Line* axisY = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 500.0, 0.0));
    Line* axisZ = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 500.0));

    Color* colorRed = new Color(1.0, 0.0, 0.0, 1.0);
    Color* colorGreen = new Color(0.0, 1.0, 0.0, 1.0);
    Color* colorBlue = new Color(0.0, 0.0, 1.0, 1.0);

    Module::sceneMan().addNode(colorRed);
    Module::sceneMan().addNode(new Texture());
    Module::sceneMan().addNode(new Cube(2.0));
    //Module::sceneMan().addNode(axisX);
    //Module::sceneMan().addNode(colorGreen);
    //Module::sceneMan().addNode(axisY);
    //Module::sceneMan().addNode(colorBlue);
    //Module::sceneMan().addNode(axisZ);

    //Module::sceneMan().open("./resource/scene.txt");

//     BSP* bsp = new BSP();
//     bsp->load("resource/bsp/test1.bsp");
//     Module::sceneMan().addNode(bsp);

    // add objects
    //     Terrain* terrain = new Terrain("resource/coastMountain64.raw", 64, 64, 10, 0.5f);
    //     Module::sceneMan().addNode(terrain);


    Module::sceneMan().print();
}
