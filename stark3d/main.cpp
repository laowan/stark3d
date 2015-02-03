#include <glload/gl_3_3.h>
#include <glload/gl_load.hpp>
#include <GL/freeglut.h>

#include <stdio.h>
#include "modules.h"
#include "utils/matrix.h"
#include "utils/shadermanager.h"
#include "scene/scene.h"
#include "scene/terrain.h"
#include "scene/cube.h"
#include "scene/line.h"

#include <glm/gtc/type_ptr.hpp>

using namespace Util;
using namespace Scene;

double gsExtent = 200.0;
int gsPixWidth;
int gsPixHeight;
double gsHpixScale; // 投影空间中一个单位对应屏幕上多少个像素
double gsVpixScale;
Matrix gsModelMat;
Matrix gsViewMat;  // view to world
glm::mat4 gsProjMat;

Matrix gsTmpMat;
int gsTmpX;
int gsTmpY;
int gsMoveBtn;

GLuint vertexBufferObject;


struct _shaderUniforms
{
    GLuint mvpUniform;
    GLuint color;
    GLuint lightPosition;
    GLuint lightColor;
} gsUniforms;

glm::mat4 getPerspectiveProjMat()
{
    // http://www.songho.ca/opengl/gl_projectionmatrix.html
    glm::mat4 mat;
    double h_w = (double)gsPixHeight / gsPixWidth;
    double r, t;

    if (h_w > 1.0)
    {
        r = gsExtent / 2.0;
        t = gsExtent * h_w / 2.0;
    }
    else
    {
        r = gsExtent / h_w / 2.0;
        t = gsExtent / 2.0;
    }

    float n = 100.0, f = -100.0;
    mat[0].x = n / r; mat[1].x = 0.0;   mat[2].x = 0.0;         mat[3].x = 0.0;
    mat[0].y = 0.0;   mat[1].y = n / t; mat[2].y = 0.0;         mat[3].y = 0.0;
    mat[0].z = 0.0;   mat[1].z = 0.0;   mat[2].z = (f+n)/(n-f); mat[3].z = 2*f*n/(n-f);
    mat[0].w = 0.0;   mat[1].w = 0.0;   mat[2].w = -1.0;        mat[3].w = 0.0;
    return mat;
}

glm::mat4 getOrthographicProjMat()
{
    glm::mat4 mat;
    double h_w = (double)gsPixHeight / gsPixWidth;
    double r, t;

    if (h_w > 1.0)
    {
        r = gsExtent / 2.0;
        t = gsExtent * h_w / 2.0;
    }
    else
    {
        r = gsExtent / h_w / 2.0;
        t = gsExtent / 2.0;
    }

    float n = 100.0, f = -100.0;
    mat[0].x = 1.0/r; mat[1].x = 0.0;   mat[2].x = 0.0;       mat[3].x = 0.0;
    mat[0].y = 0.0;   mat[1].y = 1.0/t; mat[2].y = 0.0;       mat[3].y = 0.0;
    mat[0].z = 0.0;   mat[1].z = 0.0;   mat[2].z = 2.0/(n-f); mat[3].z = (f+n)/(n-f);
    mat[0].w = 0.0;   mat[1].w = 0.0;   mat[2].w = 0.0;       mat[3].w = 1.0;
    return mat;
}

glm::mat4 getModelViewProjMat()
{
    // mat is the inverse matrix of gsViewMat
    // from world coordinate to view coordinate
    Matrix mat;
    mat.xx = gsViewMat.xx; mat.yx = gsViewMat.xy; mat.zx = gsViewMat.xz;
    mat.xy = gsViewMat.yx; mat.yy = gsViewMat.yy; mat.zy = gsViewMat.yz;
    mat.xz = gsViewMat.zx; mat.yz = gsViewMat.zy; mat.zz = gsViewMat.zz;

    mat.xt = -gsViewMat.xx*gsViewMat.xt - gsViewMat.xy*gsViewMat.yt - gsViewMat.xz*gsViewMat.zt;
    mat.yt = -gsViewMat.yx*gsViewMat.xt - gsViewMat.yy*gsViewMat.yt - gsViewMat.yz*gsViewMat.zt;
    mat.zt = -gsViewMat.zx*gsViewMat.xt - gsViewMat.zy*gsViewMat.yt - gsViewMat.zz*gsViewMat.zt;

    glm::mat4 mvMat = mat.glMatrix();
    glm::mat4 projMat = getOrthographicProjMat();
    glm::mat4 mvpMat = projMat * mvMat;
    
    return mvpMat;
}

void MouseMotion(int x, int y)
{
    printf("mouse motion (%d, %d)\n", x, y);

    if (gsMoveBtn == 1) // middle button, pan
    {
        gsViewMat = gsTmpMat;
        double dx, dy, dz;
        dx = (gsTmpX - x) / gsHpixScale;
        dy = (y - gsTmpY) / gsVpixScale;
        dz = 0;

        // transfer (dx, dy, dz) to world space
        double tmpX, tmpY, tmpZ;
        tmpX = gsViewMat.xx * dx + gsViewMat.yx * dy + gsViewMat.zx * dz + gsViewMat.xt;
        tmpY = gsViewMat.xy * dx + gsViewMat.yy * dy + gsViewMat.zy * dz + gsViewMat.yt;
        tmpZ = gsViewMat.xz * dx + gsViewMat.yz * dy + gsViewMat.zz * dz + gsViewMat.zt;

        dx = tmpX;
        dy = tmpY;
        dz = tmpZ;

        gsViewMat.xt = dx;
        gsViewMat.yt = dy;
        gsViewMat.zt = dz;
    }

    if (gsMoveBtn == 2) // right mouse button, rot
    {
        gsViewMat = gsTmpMat;

        double factor = 4.0 * (1.57079632679489661923 / gsExtent);
        double ang_y = factor * (gsTmpX - x) / gsHpixScale;
        double ang_x = factor * (gsTmpY - y) / gsVpixScale;

        Matrix& mat = gsViewMat;
        gsViewMat.rot(mat.yx, mat.yy, mat.yz, ang_y);
        gsViewMat.rot(mat.xx, mat.xy, mat.xz, ang_x);
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
        gsTmpMat = gsViewMat;
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

    double zoomFactor;
    zoomFactor = 1.0 + (160.0/(gsExtent*gsHpixScale)) * fabs((double)direction);

    if (direction > 0)
        gsExtent = gsExtent/zoomFactor;
    else
        gsExtent = gsExtent*zoomFactor;

    if (gsPixHeight > gsPixWidth)
    {
        gsHpixScale = gsPixWidth / gsExtent;
        gsVpixScale = gsHpixScale;
    }
    else
    {
        gsVpixScale = gsPixHeight / gsExtent;
        gsHpixScale = gsVpixScale;
    }

    glutPostRedisplay();
}

static void resize(int width, int height)
{
    gsPixWidth = width;
    gsPixHeight = height;

    if (gsPixHeight > gsPixWidth)
    {
        gsHpixScale = gsPixWidth / gsExtent;
        gsVpixScale = gsHpixScale;
    }
    else
    {
        gsVpixScale = gsPixHeight / gsExtent;
        gsHpixScale = gsVpixScale;
    }

    glViewport(0, 0, width, height);
}

static void init(void)
{
    Modules::init();

    // add the scene nodes
    Cube *cube = new Scene::Cube();
    Terrain *terrain = new Scene::Terrain("resource/coastMountain64.raw", 64, 64, 10, 0.5f);
    Line *line = new Scene::Line();

    Modules::sceneManager().addNode(cube);
    //Modules::sceneManager().addNode(line);
    //Modules::sceneManager().addNode(terrain);


    ShaderManager* sm = ShaderManager::instance();
    sm->use(ShaderManager::SD_NORMAL); 

    Shader* sd = sm->getShader(ShaderManager::SD_NORMAL);
    int program = sd->program();

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "normal");

    gsUniforms.mvpUniform = glGetUniformLocation(program, "uModelViewProjMat");
    gsUniforms.color = glGetUniformLocation(program, "uColor");
    gsUniforms.lightPosition = glGetUniformLocation(program, "uLightPosition");
    gsUniforms.lightColor = glGetUniformLocation(program, "uLightColor");

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
//     glDisable(GL_CULL_FACE);
//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glDisable(GL_BLEND);

}

static void display(void)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderManager* sm = ShaderManager::instance();
    sm->use(ShaderManager::SD_NORMAL);

    // calculate the mvp matrix and apply it to the shader
    glm::mat4 mvp = getModelViewProjMat();
    glUniformMatrix4fv(gsUniforms.mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));

    glm::vec4 c1(0.0, 1.0, 0.0, 1.0);
    glUniform4fv(gsUniforms.color, 1, glm::value_ptr(c1));

    glm::vec3 lightPos(200.0f, 200.0f, 200.0f);
    glUniform3fv(gsUniforms.lightPosition, 1, glm::value_ptr(lightPos));

    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glUniform3fv(gsUniforms.lightColor, 1, glm::value_ptr(lightColor));

    // now render the scene
    Modules::sceneManager().render();

//     glm::vec4 c2(0.0, 0.0, 0.0, 1.0);
//     glUniform4fv(color, 1, glm::value_ptr(c2));
//     Line *line = new Scene::Line();
//     line->render();

    glutSwapBuffers();
    glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'Q':
    case 'q': glutLeaveMainLoop();      break;
    case 's':
        {
        gsViewMat = Matrix();
        break;
        }
    default:
        break;
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
