#include "utils.h"
#include "external/edtaa3func/edtaa3func.h"
#include "stdlib.h"

unsigned char* makeDistanceMap(unsigned char *img, int width, int height, int distanceMapSpread)
{
    long pixelAmount = (width + 2 * distanceMapSpread) * (height + 2 * distanceMapSpread);

    short * xdist = (short *)malloc(pixelAmount * sizeof(short));
    short * ydist = (short *)malloc(pixelAmount * sizeof(short));
    double * gx = (double *)calloc(pixelAmount, sizeof(double));
    double * gy = (double *)calloc(pixelAmount, sizeof(double));
    double * data = (double *)calloc(pixelAmount, sizeof(double));
    double * outside = (double *)calloc(pixelAmount, sizeof(double));
    double * inside = (double *)calloc(pixelAmount, sizeof(double));
    long i, j;

    // Convert img into double (data) rescale image levels between 0 and 1
    long outWidth = width + 2 * distanceMapSpread;
    for (i = 0; i < width; ++i)
    {
        for (j = 0; j < height; ++j)
        {
            data[j * outWidth + distanceMapSpread + i] = img[j * width + i] / 255.0;
        }
    }

    width += 2 * distanceMapSpread;
    height += 2 * distanceMapSpread;

    // Transform background (outside contour, in areas of 0's)   
    computegradient(data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, outside);
    for (i = 0; i< pixelAmount; i++)
        if (outside[i] < 0.0)
            outside[i] = 0.0;

    // Transform foreground (inside contour, in areas of 1's)   
    for (i = 0; i< pixelAmount; i++)
        data[i] = 1 - data[i];
    computegradient(data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, inside);
    for (i = 0; i< pixelAmount; i++)
        if (inside[i] < 0.0)
            inside[i] = 0.0;

    // The bipolar distance field is now outside-inside
    double dist;
    /* Single channel 8-bit output (bad precision and range, but simple) */
    unsigned char *out = (unsigned char *)malloc(pixelAmount * sizeof(unsigned char));
    for (i = 0; i < pixelAmount; i++)
    {
        dist = outside[i] - inside[i];
        dist = 128.0 - dist * 16;
        if (dist < 0) dist = 0;
        if (dist > 255) dist = 255;
        out[i] = (unsigned char)dist;
    }
    /* Dual channel 16-bit output (more complicated, but good precision and range) */
    /*unsigned char *out = (unsigned char *) malloc( pixelAmount * 3 * sizeof(unsigned char) );
    for( i=0; i< pixelAmount; i++)
    {
    dist = outside[i] - inside[i];
    dist = 128.0 - dist*16;
    if( dist < 0.0 ) dist = 0.0;
    if( dist >= 256.0 ) dist = 255.999;
    // R channel is a copy of the original grayscale image
    out[3*i] = img[i];
    // G channel is fraction
    out[3*i + 1] = (unsigned char) ( 256 - (dist - floor(dist)* 256.0 ));
    // B channel is truncated integer part
    out[3*i + 2] = (unsigned char)dist;
    }*/

    free(xdist);
    free(ydist);
    free(gx);
    free(gy);
    free(data);
    free(outside);
    free(inside);

    return out;
}

// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include <stb_image_write.h>

// using namespace SK;

// void skScreenshot(const char* file)
// {
//     int width = Module::sceneMan().getCamera()->getViewport().pixWidth;
//     int height = Module::sceneMan().getCamera()->getViewport().pixHeight;
// 
//     GLuint fbo;
//     glGenFramebuffers(1, &fbo);
//     glBindFramebuffer(GL_FRAMEBUFFER, fbo);
// 
//     GLuint colortexture;
//     glGenTextures(1, &colortexture);
//     glBindTexture(GL_TEXTURE_2D, colortexture);
// 
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 
//     //glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//     //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colortexture, 0);
//     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colortexture, 0);
// 
//     GLuint depthtexture;
//     glGenTextures(1, &depthtexture);
//     glBindTexture(GL_TEXTURE_2D, depthtexture);
//     //glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, width, height);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
//     //glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthtexture, 0);
//     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthtexture, 0);
// 
// 
//     static const GLenum draw_buffer[] = { GL_COLOR_ATTACHMENT0 };
//     glDrawBuffers(1, draw_buffer);
// 
//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
//     glBindTexture(GL_TEXTURE_2D, 0);
// 
//     /*
//     draw something
//     */
//     glBindFramebuffer(GL_FRAMEBUFFER, fbo);
// 
//     //gsCam->getViewport().resize(width, height);
//     glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//     glClearDepth(1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
//     Module::resMan().useShader("normal");
// 
//     ShaderUniforms& uniforms = Module::resMan().currentShader()->uniforms();
// 
//     // calculate the mvp matrix and apply it to the shader
//     uniforms.mvp = Module::sceneMan().getCamera()->getViewProjMat();
//     uniforms.color = glm::vec4(1.0, 1.0, 0.0, 1.0);
//     uniforms.lightPosition = glm::vec3(300.0f, 300.0f, 300.0f);
//     uniforms.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
//     uniforms.activeTexture = 0;
// 
//     Module::resMan().currentShader()->commitUniforms();
// 
//     // now render the scene
//     Module::sceneMan().render();
// 
//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
// 
//     /*
//     generate the image
//     */
//     glBindTexture(GL_TEXTURE_2D, colortexture);
//     unsigned char* pdata = (unsigned char*)malloc(sizeof(unsigned char)* 4 * width * height);
//     memset(pdata, 0, sizeof(char)* 3 * width * height);
//     glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pdata);
//     glBindTexture(GL_TEXTURE_2D, 0);
// 
//     //stbi_write_bmp(file, width, height, 4, pdata);
//     free(pdata);
// }
// 
// void skCreateScene1()
// {
//     Module::sceneMan().clear();
// 
//     Module::sceneMan().addNode(new Texture());
//     Module::sceneMan().addNode(new Mesh("./resource/Teapot.3ds"));
// 
//     //Module::sceneMan().addNode(axisX);
//     //Module::sceneMan().addNode(colorGreen);
//     //Module::sceneMan().addNode(axisY);
//     //Module::sceneMan().addNode(colorBlue);
//     //Module::sceneMan().addNode(axisZ);
// 
//     //Module::sceneMan().open("./resource/scene.txt");
// 
// //     BSP* bsp = new BSP();
// //     bsp->load("resource/bsp/test1.bsp");
// //     Module::sceneMan().addNode(bsp);
// 
//     // add objects
//     //     Terrain* terrain = new Terrain("resource/coastMountain64.raw", 64, 64, 10, 0.5f);
//     //     Module::sceneMan().addNode(terrain);
// 
// 
//     Module::sceneMan().print();
// }
// 
// void skCreateScene2()
// {
//     Module::sceneMan().clear();
// 
//     // add three coordinate axes
//     Line* axisX = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(500.0, 0.0, 0.0));
//     Line* axisY = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 500.0, 0.0));
//     Line* axisZ = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 500.0));
// 
//     Color* colorRed = new Color(1.0, 0.0, 0.0, 1.0);
//     Color* colorGreen = new Color(0.0, 1.0, 0.0, 1.0);
//     Color* colorBlue = new Color(0.0, 0.0, 1.0, 1.0);
// 
//     Module::sceneMan().addNode(colorRed);
//     Module::sceneMan().addNode(new Texture("./resource/earth.jpg"));
//     Module::sceneMan().addNode(new Mesh("./resource/Sphere.3ds"));
// 
//     Module::sceneMan().print();
// }


#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    //
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    //
    static const SKUInt64 EPOCH = ((SKUInt64)116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    SKUInt64    time;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    time = ((SKUInt64)file_time.dwLowDateTime);
    time += ((SKUInt64)file_time.dwHighDateTime) << 32;

    tp->tv_sec = (long)((time - EPOCH) / 10000000L);
    tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
    return 0;
}
#endif

SKUInt64 CurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (SKUInt64)tv.tv_sec * 1000ULL + tv.tv_usec / 1000;
}
