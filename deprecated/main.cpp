﻿#define USE_VULKAN

#ifdef USE_VULKAN

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}

#else
#include "GL/glew.h"
#include "GL/wglew.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "stark3d.h"
#include "utils/math.h"
#include "scene/camera.h"

bool sRightBtnDown = false;
SK::Vector2 sBeginPos;
SK::Matrix4 sViewMat;
SK::Scene* sScene = nullptr;

static const char* titles[] =
{
    "Red",
    "Green",
    "Blue",
    "Yellow"
};

static const struct
{
    float r, g, b;
} colors[] =
{
    { 0.95f, 0.32f, 0.11f },
    { 0.50f, 0.80f, 0.16f },
    {   0.f, 0.68f, 0.94f },
    { 0.98f, 0.74f, 0.04f }
};

static void usage(void)
{
    printf("Usage: window [-h] [-b] [-f] \n");
    printf("Options:\n");
    printf("  -b create decorated window\n");
    printf("  -f set focus on show off for all but first window\n");
    printf("  -h show this help\n");
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
    case GLFW_KEY_SPACE:
    {
        int xpos, ypos;
        glfwGetWindowPos(window, &xpos, &ypos);
        glfwSetWindowPos(window, xpos, ypos);
        break;
    }

    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (sRightBtnDown)
    {
        float dx = (float)xpos - sBeginPos.x;
        float dy = (float)ypos - sBeginPos.y;
        printf("dx dy %.2f, %.2f\n", dx, dy);

        SK::Matrix4 mat = SK::Matrix4::RotMat(SK::Radian(dy), SK::Radian(-dx), 0);

        SK::Camera* camera = sScene->getCamera();
        camera->setViewMatrix(sViewMat * mat);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    printf("mouse button %d, %d, %d\n", button, action, mods);
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        sRightBtnDown = true;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        sBeginPos.x = (float)xpos;
        sBeginPos.y = (float)ypos;

        SK::Camera* camera = sScene->getCamera();
        sViewMat = camera->getViewMatrix();
    }
    else
    {
        sRightBtnDown = false;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    printf("scroll %.2f, %.2f\n", xoffset, yoffset);
}

int main(int argc, char** argv)
{
    int i = 0, ch;
    int decorated = GLFW_FALSE;
    int focusOnShow = GLFW_TRUE;
    int running = GLFW_TRUE;
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    //glfwWindowHint(GLFW_DECORATED, decorated);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    int left, top, right, bottom;
    //if (i)
    //    glfwWindowHint(GLFW_FOCUS_ON_SHOW, focusOnShow);

    window = glfwCreateWindow(400, 400, titles[i], NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwMakeContextCurrent(window);
    glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);

    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
    glfwSetWindowPos(window,
        100 + (i & 1) * (200 + left + right),
        100 + (i >> 1) * (200 + top + bottom));

    glfwShowWindow(window);
        
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
        return 1;
    }

    sScene = new SK::Scene;
    sScene->loadGLTF("../res/gltf/BoxTextured/BoxTextured.gltf");

    while (running)
    {
        //glClear(GL_COLOR_BUFFER_BIT);

        sScene->update();
        sScene->render();

        glfwSwapBuffers(window);

        if (glfwWindowShouldClose(window))
            running = GLFW_FALSE;

        //glfwWaitEvents();
        glfwPollEvents();
    }

    delete sScene;
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

#endif