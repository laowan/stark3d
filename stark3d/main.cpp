#include <stdio.h>
#include <memory>
#include <iostream>

#include <GLFW/glfw3.h>

#include "scene/world.h"
#include "utils/linmath.h"

const int gsWinWidth = 800;
const int gsWinHeight = 600;

SK::World gsWorld;

static void init(void)
{
    std::string objfile = "../res/bs0_tex_simplified.obj";
    gsWorld.load(objfile);
}

static void exit(void)
{
   
}

static void display(void)
{
    gsWorld.render();
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

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    init();

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
