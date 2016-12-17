#include "game.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <time.h>

static void resize(int width, int height);
static void display(void);
static void keyboard(unsigned char key, int x, int y);
static void special(int key, int x, int y);
static void idle(void);

static const int GameWith = 280;
static const int GameHeight = 400;
static Game game;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(GameWith, GameHeight);
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    int window = glutCreateWindow("Breakout");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    SK::Module::init();

    game.init(GameWith, GameHeight);

    glutMainLoop();

    return 0;
}


static void resize(int width, int height)
{
    SK::Module::sceneMan().getCamera()->getViewport().resize(width, height);
}

static void display(void)
{
    static float lastTime = clock() / CLOCKS_PER_SEC;
    float t = (float)clock() / CLOCKS_PER_SEC;
    float deltaTime = t - lastTime;
    lastTime = t;

    game.update(deltaTime);

    SK::Module::render();
    game.render();

    glutSwapBuffers();
    glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
    game.processInput(key, 0);
    switch (key)
    {
    case 'r': SK::Module::sceneMan().getCamera()->reset(); break;
    case 'z': SK::Module::sceneMan().getCamera()->zoomAll(SK::Module::sceneMan().boundingBox()); break;
    case 'q': glutLeaveMainLoop(); break;
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