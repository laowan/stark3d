#include <stdio.h>
#include <memory>
#include <iostream>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "scene/world.h"
#include "scene/camera.h"
#include "utils/linmath.h"

const int gsWinWidth = 800;
const int gsWinHeight = 600;

SK::World gsWorld;
SK::Camera gsCamera;

float gsFov = 45;
bool gsLeftMouseBtnDown = false;
bool gsRightMouseBtnDown = false;
double gsMouseLastPosX = 0.0;
double gsMouseLastPosY = 0.0;
double gsMouseCurPosX = 0.0;
double gsMouseCurPoxY = 0.0;
vec3 gsCameraPos = { 0, 0, 3 };
vec3 gsCameraFront = { 0, 0, -1 };
vec3 gsCameraUp = { 0, 1, 0 };
vec3 gsCameraRight = { 0, 0, 0 };

static void init(int w, int h)
{
    gsCamera.getViewport().resize(w, h);
    gsCamera.setLookAt(gsCameraPos, gsCameraFront, gsCameraUp);
    gsCamera.setPerspective(gsFov / 180 * 3.1415926, (float)w / h, 0.01f, 100.0f);

    vec3_mul_cross(gsCameraRight, gsCameraFront, gsCameraUp);

    std::string file = "../res/gltf/Box/Box.gltf";
    gsWorld.load(file);
}

static void exit(void)
{
   
}

static void display(void)
{
    gsWorld.render(&gsCamera);
}

static const char* get_action_name(int action)
{
    switch (action)
    {
    case GLFW_PRESS:
        return "pressed";
    case GLFW_RELEASE:
        return "released";
    case GLFW_REPEAT:
        return "repeated";
    }

    return "caused unknown action";
}

static const char* get_button_name(int button)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        return "left";
    case GLFW_MOUSE_BUTTON_RIGHT:
        return "right";
    case GLFW_MOUSE_BUTTON_MIDDLE:
        return "middle";
    default:
    {
        static char name[16];
        snprintf(name, sizeof(name), "%i", button);
        return name;
    }
    }
}

static const char* get_mods_name(int mods)
{
    static char name[512];

    if (mods == 0)
        return " no mods";

    name[0] = '\0';

    if (mods & GLFW_MOD_SHIFT)
        strcat(name, " shift");
    if (mods & GLFW_MOD_CONTROL)
        strcat(name, " control");
    if (mods & GLFW_MOD_ALT)
        strcat(name, " alt");
    if (mods & GLFW_MOD_SUPER)
        strcat(name, " super");
    if (mods & GLFW_MOD_CAPS_LOCK)
        strcat(name, " capslock-on");
    if (mods & GLFW_MOD_NUM_LOCK)
        strcat(name, " numlock-on");

    return name;
}


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    printf("%0.3f: Mouse button %i (%s) (with%s) was %s\n",
        glfwGetTime(), button,
        get_button_name(button),
        get_mods_name(mods),
        get_action_name(action));

    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            gsLeftMouseBtnDown = true;
            gsMouseLastPosX = gsMouseCurPosX;
            gsMouseLastPosY = gsMouseCurPoxY;
        }
        else if (action == GLFW_RELEASE)
        {
            gsLeftMouseBtnDown = false;
            gsCamera.getPosition(gsCameraPos);
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            gsRightMouseBtnDown = true;
            gsMouseLastPosX = gsMouseCurPosX;
            gsMouseLastPosY = gsMouseCurPoxY;
        }
        else if (action == GLFW_RELEASE)
        {
            gsRightMouseBtnDown = false;
            gsCamera.getFrontDir(gsCameraFront);
        }
    }
}

static void cursor_position_callback(GLFWwindow* window, double x, double y)
{
    printf("%0.3f: Cursor position: %f %f\n", glfwGetTime(), x, y);

    double ratio = 0.005;
    if (gsLeftMouseBtnDown)
    {
        vec3 deltaX;
        vec3_scale(deltaX, gsCameraRight, (gsMouseLastPosX - x) * ratio);

        vec3 deltaY;
        vec3_scale(deltaY, gsCameraUp, -(gsMouseLastPosY - y) * ratio);

        vec3 pos;
        vec3_add(pos, gsCameraPos, deltaX);
        vec3_add(pos, pos, deltaY);

        gsCamera.setLookAt(pos, gsCameraFront, gsCameraUp);
    }
    else if (gsRightMouseBtnDown)
    {
        float angle = (x - gsMouseLastPosX) * ratio;
        float fx = cos(angle) * gsCameraFront[0] + sin(angle) * gsCameraFront[2];
        float fy = gsCameraFront[1];
        float fz = -sin(angle) * gsCameraFront[0] + cos(angle) * gsCameraFront[2];

        vec3 front = { fx, fy, fz };
        gsCamera.setLookAt(gsCameraPos, front, gsCameraUp);
    }

    gsMouseCurPosX = x;
    gsMouseCurPoxY = y;
}

static void scroll_callback(GLFWwindow* window, double x, double y)
{
    printf("%0.3f: Scroll: %0.3f %0.3f\n", glfwGetTime(), x, y);
    if (y > 0.0)
        gsFov += 1.0;
    else
        gsFov -= 1.0;

    gsCamera.setPerspective(gsFov / 180 * 3.1415926, (float)gsWinWidth / gsWinHeight, 0.01f, 100.0f);
}

int mainloop()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(gsWinWidth, gsWinHeight, "Stark", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        return -1;
    }

    init(gsWinWidth, gsWinHeight);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        display();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    exit();

    glfwTerminate();
    return 0;
}

int mainxx(int argc, char *argv[])
{
    mainloop();
    return 0;
}
