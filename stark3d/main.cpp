#include <glload/gl_3_3.h>
#include <glload/gl_load.hpp>
#include <GL/freeglut.h>

#include <stdio.h>

#include "utils/shadermanager.h"

using namespace Util::Shader;

const float vertexData[] = {
    0.25f, 0.25f, 0.75f, 1.0f,
    0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f, 0.25f, 0.75f, 1.0f,

    0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f, 0.25f, 0.75f, 1.0f,

    0.25f, 0.25f, -0.75f, 1.0f,
    -0.25f, 0.25f, -0.75f, 1.0f,
    0.25f, -0.25f, -0.75f, 1.0f,

    0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, 0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,

    -0.25f, 0.25f, 0.75f, 1.0f,
    -0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,

    -0.25f, 0.25f, 0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, 0.25f, -0.75f, 1.0f,

    0.25f, 0.25f, 0.75f, 1.0f,
    0.25f, -0.25f, -0.75f, 1.0f,
    0.25f, -0.25f, 0.75f, 1.0f,

    0.25f, 0.25f, 0.75f, 1.0f,
    0.25f, 0.25f, -0.75f, 1.0f,
    0.25f, -0.25f, -0.75f, 1.0f,

    0.25f, 0.25f, -0.75f, 1.0f,
    0.25f, 0.25f, 0.75f, 1.0f,
    -0.25f, 0.25f, 0.75f, 1.0f,

    0.25f, 0.25f, -0.75f, 1.0f,
    -0.25f, 0.25f, 0.75f, 1.0f,
    -0.25f, 0.25f, -0.75f, 1.0f,

    0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, 0.75f, 1.0f,
    0.25f, -0.25f, 0.75f, 1.0f,

    0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, 0.75f, 1.0f,




    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,

    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,

    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

};

GLuint vertexBufferObject;
GLuint vao;
GLuint offsetUniform;

void MouseMotion(int x, int y)
{
    printf("mouse motion (%d, %d)\n", x, y);
    glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y)
{
    printf("mouse button %d, %d, (%d, %d)\n", button, state, x, y);
    glutPostRedisplay();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    printf("mouse wheel %d, %d, (%d, %d)\n", wheel, direction, x, y);
    glutPostRedisplay();
}

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

static void init(void)
{
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShaderManager* sm = ShaderManager::instance();
    sm->use(ShaderManager::SD_NORMAL); 
    
    Shader* sd = sm->getShader(ShaderManager::SD_NORMAL);
    int program = sd->program();

    offsetUniform = glGetUniformLocation(program, "offset");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

}

static void display(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ShaderManager* sm = ShaderManager::instance();
    sm->use(ShaderManager::SD_NORMAL);

    glUniform2f(offsetUniform, 0.0f, 0.0f);
    size_t colorData = sizeof(vertexData) / 2;


    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


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
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(40, 40);
    glutInit(&argc, argv);
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

    if (!glload::IsVersionGEQ(3, 3))
    {
        printf("Your OpenGL version is %i, %i. You must have at least OpenGL 3.3 to run this tutorial.\n",
            glload::GetMajorVersion(), glload::GetMinorVersion());
        glutDestroyWindow(window);
        return 0;
    }


    init();

    glutMainLoop();

    return 0;
}
