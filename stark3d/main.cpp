#include <stdio.h>
#include <memory>

#include <GLFW/glfw3.h>

// #include "bgfx/bgfx.h"
// #include "bgfx/platform.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include <iostream>

//using namespace SK;

const int gsWinWidth = 800;
const int gsWinHeight = 600;

static void init(void)
{

// 	bgfx::renderFrame();
// 
//     bgfx::Init init;
//     init.type = bgfx::RendererType::OpenGL;
//     init.vendorId = BGFX_PCI_ID_NONE;
//     init.resolution.width = gsWinWidth;
//     init.resolution.height = gsWinHeight;
//     init.resolution.reset = BGFX_RESET_VSYNC;
//     bgfx::init(init);
// 
//     bgfx::setDebug(BGFX_DEBUG_TEXT);
//     bgfx::setViewClear(0
//         , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
//         , 0x303030ff
//         , 1.0f
//         , 0
//     );

    std::string objfile = "../res/bs0_tex_simplified.obj";

    Assimp::Importer imp;
    const aiScene* scene = imp.ReadFile(objfile, 0);

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objfile.c_str());

    if (!warn.empty())
    {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) 
    {
        std::cerr << "ERR: " << err << std::endl;
    }

    if (!ret) 
    {
        printf("Failed to load/parse .obj.\n");
    }

}

static void display(void)
{
//     // Set view 0 default viewport.
//     bgfx::setViewRect(0, 0, 0, uint16_t(gsWinWidth), uint16_t(gsWinHeight));
// 
//     // This dummy draw call is here to make sure that view 0 is cleared
//     // if no other draw calls are submitted to view 0.
//     bgfx::touch(0);
// 
//     bgfx::dbgTextClear();
// 
//     bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
//     bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
//     bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
// 
//     const bgfx::Stats* stats = bgfx::getStats();
//     bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
//         , stats->width
//         , stats->height
//         , stats->textWidth
//         , stats->textHeight
//     );
// 
//     bgfx::frame();
}

int main(int argc, char *argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(gsWinWidth, gsWinHeight, "Hello World", NULL, NULL);
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

    glfwTerminate();
    return 0;
}
