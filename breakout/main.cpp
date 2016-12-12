#include "stark3d.h"
#include <GL/freeglut.h>

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(40, 40);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    int window = glutCreateWindow("Breakout");

//     glutReshapeFunc(resize);
//     glutDisplayFunc(display);
//     glutKeyboardFunc(keyboard);
//     glutSpecialFunc(special);
//     glutIdleFunc(idle);
// 
//     glutMouseFunc(MouseButton);
//     glutMotionFunc(MouseMotion);
//     glutPassiveMotionFunc(PassiveMotion);
//     glutMouseWheelFunc(MouseWheel);
// 
//     glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
// 
//     glload::LoadTest test = glload::LoadFunctions();
//     if (!test)
//     {
//         printf("err when glload init\n");
//         return 1;
//     }
// 
//     init();
    SK::Module::init();
    SK::Module::sceneMan().print();

    glutMainLoop();

    return 0;
}
