#include <stdio.h>
#include <memory>

#include <GLFW/glfw3.h>

#include "bx/math.h"
#include "bx/timer.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include <iostream>

#include "learnsomething/learnsomething.h"
#include "utils/bgfxutils.h"
#include "resources.h"

//using namespace SK;

const int gsWinWidth = 800;
const int gsWinHeight = 600;

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

static const uint16_t s_cubeTriStrip[] =
{
    0, 1, 2,
    3,
    7,
    1,
    5,
    0,
    4,
    2,
    6,
    7,
    4,
    5,
};

bgfx::VertexBufferHandle m_vbh;
bgfx::IndexBufferHandle m_ibh;
bgfx::ProgramHandle m_program;
int64_t m_timeOffset;

static void init(void)
{
	bgfx::renderFrame();

    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.resolution.width = gsWinWidth;
    init.resolution.height = gsWinHeight;
    init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(init);

    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , 0x303030ff
        , 1.0f
        , 0
    );

    // Create vertex stream declaration.
    PosColorVertex::init();

    // Create static vertex buffer.
    m_vbh = bgfx::createVertexBuffer(
        // Static data can be passed with bgfx::makeRef
        bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
        , PosColorVertex::ms_decl
    );

    // Create static index buffer for triangle strip rendering.
    m_ibh = bgfx::createIndexBuffer(
        // Static data can be passed with bgfx::makeRef
        bgfx::makeRef(s_cubeTriStrip, sizeof(s_cubeTriStrip))
    );

    // Create program from shaders.
    m_program = loadProgram("vs_cubes", "fs_cubes");

    m_timeOffset = bx::getHPCounter();

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

static void exit(void)
{
    bgfx::destroy(m_vbh);
    bgfx::destroy(m_ibh);
    bgfx::destroy(m_program);

    // Shutdown bgfx.
    bgfx::shutdown();
}

static void display(void)
{
    float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

    // Set view 0 default viewport.
    bgfx::setViewRect(0, 0, 0, uint16_t(gsWinWidth), uint16_t(gsWinHeight));

    // This dummy draw call is here to make sure that view 0 is cleared
    // if no other draw calls are submitted to view 0.
    bgfx::touch(0);

    bgfx::dbgTextClear();

    bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
    bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
    bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

    const bgfx::Stats* stats = bgfx::getStats();
    bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
        , stats->width
        , stats->height
        , stats->textWidth
        , stats->textHeight
    );

    float at[3] = { 0.0f, 0.0f,   0.0f };
    float eye[3] = { 0.0f, 0.0f, -35.0f };

    // Set view and projection matrix for view 0.
    {
        float view[16];
        bx::mtxLookAt(view, eye, at);

        float proj[16];
        bx::mtxProj(proj, 60.0f, float(gsWinWidth) / float(gsWinHeight), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);

        // Set view 0 default viewport.
        bgfx::setViewRect(0, 0, 0, uint16_t(gsWinWidth), uint16_t(gsWinHeight));
    }

    uint64_t state = 0
        | BGFX_STATE_WRITE_R
        | BGFX_STATE_WRITE_G
        | BGFX_STATE_WRITE_B
        | BGFX_STATE_WRITE_A
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_CULL_CW
        | BGFX_STATE_MSAA
        | BGFX_STATE_PT_TRISTRIP
        ;

    float mtx[16];
    bx::mtxRotateXY(mtx, time, time);

    // Set model matrix for rendering.
    bgfx::setTransform(mtx);

    // Set vertex and index buffer.
    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);

    // Set render states.
    bgfx::setState(state);

    // Submit primitive for rendering to view 0.
    bgfx::submit(0, m_program);

    bgfx::frame();
}

int mainloop()
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

    exit();

    glfwTerminate();
    return 0;
}

int main(int argc, char *argv[])
{
    std::string path = "../res/gltf/Triangle/Triangle.gltf";
    SK::Resources::LoadGltf(path);

    //LearnSdf();
    mainloop();
    return 0;
}
