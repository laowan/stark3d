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

static void init(int w, int h)
{
    gsCamera.getViewport().resize(w, h);

    std::string objfile = "../res/bs0_tex_simplified.obj";
    gsWorld.load(objfile);
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
}

static void cursor_position_callback(GLFWwindow* window, double x, double y)
{
    printf("%0.3f: Cursor position: %f %f\n", glfwGetTime(), x, y);
}

static void scroll_callback(GLFWwindow* window, double x, double y)
{
    printf("%0.3f: Scroll: %0.3f %0.3f\n", glfwGetTime(), x, y);
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

int main(int argc, char *argv[])
{
    mainloop();
    return 0;
}
