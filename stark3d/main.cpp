#include <glload/gl_3_3.h>
#include <glload/gl_load.hpp>
#include <GL/freeglut.h>

#include <stdio.h>
#include "module.h"
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace SK;

Matrix gsTmpMat;
int gsTmpX;
int gsTmpY;
int gsMoveBtn;

Camera* gsCam = NULL;

void MouseMotion(int x, int y)
{
    printf("mouse motion (%d, %d)\n", x, y);

    Viewport& vp = gsCam->getViewport();
    Matrix& viewMat = gsCam->getViewMat();
    if (gsMoveBtn == 1) // middle button, pan
    {
        viewMat = gsTmpMat;
        double dx, dy, dz;
        dx = (gsTmpX - x) / vp._hpixScale;
        dy = (y - gsTmpY) / vp._vpixScale;
        dz = 0;

        // transfer (dx, dy, dz) to world space
        double tmpX, tmpY, tmpZ;
        tmpX = viewMat.xx * dx + viewMat.yx * dy + viewMat.zx * dz + viewMat.xt;
        tmpY = viewMat.xy * dx + viewMat.yy * dy + viewMat.zy * dz + viewMat.yt;
        tmpZ = viewMat.xz * dx + viewMat.yz * dy + viewMat.zz * dz + viewMat.zt;

        dx = tmpX;
        dy = tmpY;
        dz = tmpZ;

        viewMat.xt = dx;
        viewMat.yt = dy;
        viewMat.zt = dz;
    }

    if (gsMoveBtn == 2) // right mouse button, rot
    {
        viewMat = gsTmpMat;

        double factor = 4.0 * (1.57079632679489661923 / vp._extent);
        double ang_y = factor * (gsTmpX - x) / vp._hpixScale;
        double ang_x = factor * (gsTmpY - y) / vp._vpixScale;

        Matrix& mat = viewMat;
        viewMat.rot(mat.yx, mat.yy, mat.yz, ang_y);
        viewMat.rot(mat.xx, mat.xy, mat.xz, ang_x);
    }

    glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y)
{
    if (state == 0)
    {
        gsMoveBtn = button;
        gsTmpX = x;
        gsTmpY = y;
        gsTmpMat = gsCam->getViewMat();
    }
    else
    {
        gsMoveBtn = -1;
    }

    printf("mouse button %d, %d, (%d, %d)\n", button, state, x, y);
    glutPostRedisplay();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    printf("mouse wheel %d, %d, (%d, %d)\n", wheel, direction, x, y);

    Viewport& vp = gsCam->getViewport();
    double zoomFactor;
    zoomFactor = 1.0 + (160.0/(vp._extent*vp._vpixScale)) * fabs((double)direction);

    if (direction > 0)
        vp._extent = vp._extent/zoomFactor;
    else
        vp._extent = vp._extent*zoomFactor;

    if (vp._pixHeight > vp._pixWidth)
    {
        vp._hpixScale = vp._pixWidth / vp._extent;
        vp._vpixScale = vp._hpixScale;
    }
    else
    {
        vp._vpixScale = vp._pixHeight / vp._extent;
        vp._hpixScale = vp._vpixScale;
    }

    glutPostRedisplay();
}

static void resize(int width, int height)
{
    gsCam->getViewport().resize(width, height);
}

static void init(void)
{
    Module::init();

    gsCam = new Camera();
    Module::sceneMan().addNode(gsCam);

    // add three coordinate axes
    Line* axisX = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(500.0, 0.0, 0.0));
    Line* axisY = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 500.0, 0.0));
    Line* axisZ = new Line(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 500.0));

    Color* colorRed = new Color(1.0, 0.0, 0.0, 1.0);
    Color* colorGreen = new Color(0.0, 1.0, 0.0, 1.0);
    Color* colorBlue = new Color(0.0, 0.0, 1.0, 1.0);

    Module::sceneMan().addNode(colorRed);
    Module::sceneMan().addNode(axisX);
    Module::sceneMan().addNode(colorGreen);
    Module::sceneMan().addNode(axisY);
    Module::sceneMan().addNode(colorBlue);
    Module::sceneMan().addNode(axisZ);


    // add objects
//     Terrain* terrain = new Terrain("resource/coastMountain64.raw", 64, 64, 10, 0.5f);
//     Module::sceneMan().addNode(terrain);
    Module::sceneMan().addNode(new Color(1.0, 1.0, 0.0, 1.0));
    Module::sceneMan().addNode(new Texture());
    Module::sceneMan().addNode(new Cube(50.0));

//     Transform* transform1 = new Transform();
//     Matrix& mat = transform1->matrix();
//     mat.pan(50.0, 0.0, 0.0);
//     Module::sceneMan().addNode(transform1);
// 
//     Module::sceneMan().addNode(new Color(0.0, 1.0, 0.0, 1.0));
//     Module::sceneMan().addNode(new Cube(50.0));
// 
//     Transform* transform2 = new Transform();
//     mat = transform2->matrix();
//     mat.pan(50.0, 0.0, 0.0);
//     Module::sceneMan().addNode(transform2);
// 
//     Module::sceneMan().addNode(new Color(0.0, 0.0, 1.0, 1.0));
//     Module::sceneMan().addNode(new Cube(50.0));
// 
//     Module::sceneMan().print();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    glDisable(GL_BLEND);

}

static void display(void)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Module::shaderMan().use(ShaderManager::SD_NORMAL);

    ShaderUniforms& uniforms = Module::shaderMan().currentShader()->uniforms();

    // calculate the mvp matrix and apply it to the shader
    uniforms.mvp = gsCam->getViewProjMat();
    uniforms.color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    uniforms.lightPosition = glm::vec3(300.0f, 300.0f, 300.0f);
    uniforms.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    uniforms.activeTexture = 0;

    Module::shaderMan().currentShader()->commitUniforms();

    // now render the scene
    Module::sceneMan().render();

    glutSwapBuffers();
    glutPostRedisplay();
}

void test_framebuffer()
{
	int width = gsCam->getViewport()._pixWidth;
	int height = gsCam->getViewport()._pixHeight;
	
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

    Module::shaderMan().use(ShaderManager::SD_NORMAL);

    ShaderUniforms& uniforms = Module::shaderMan().currentShader()->uniforms();

    // calculate the mvp matrix and apply it to the shader
    uniforms.mvp = gsCam->getViewProjMat();
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

    stbi_write_bmp("123.bmp", width, height, 4, pdata);
    free(pdata);
 
}

static void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q': glutLeaveMainLoop(); break;
    case 's': gsCam->reset(); break;
	case '1': test_framebuffer(); break;
    default: break;
    }

    glutPostRedisplay();
}

static void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_PAGE_UP:    break;
    case GLUT_KEY_PAGE_DOWN:  break;
    case GLUT_KEY_UP:         break;
    case GLUT_KEY_DOWN:       break;
    case GLUT_KEY_RIGHT:      break;
    case GLUT_KEY_LEFT:       break;

    default:
        break;
    }
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(40, 40);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    int window = glutCreateWindow("Stark 3D");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMotion);
    glutMouseWheelFunc(MouseWheel);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glload::LoadTest test = glload::LoadFunctions();
    if (!test)
    {
        printf("err when glload init\n");
        return 1;
    }

    init();

    glutMainLoop();

    return 0;
}
