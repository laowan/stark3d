#include <glload/gl_3_3_comp.h>
#include <glload/gl_load.h>

#include <stdio.h>
#include <memory>

#include "module.h"
#include "effect.h"
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#include <GL/freeglut.h>

using namespace SK;

Matrix gsTmpMat;
int gsTmpX;
int gsTmpY;
int gsMoveBtn;
static GLuint gsFontTexture = 0;
static bool gsMousePressed[3] = { false, false, false };
static int gsScreenshotButton = 0;

static std::unique_ptr<Effect> gsEffect;
static bool gsEffectNormal = false;
static bool gsEffectScreenTextureMap = false;
static bool gsEffectMotionBlur = false;
static bool gsScene1 = false;
static bool gsScene2 = false;

const int gsWinWidth = 800;
const int gsWinHeight = 600;

void ImGuiRenderDrawLists(ImDrawData* draw_data)
{
    // We are using the OpenGL fixed pipeline to make the example code simpler to read!
    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers.
    GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_TEXTURE_2D);
    glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context

    // Handle cases of screen coordinates != from framebuffer coordinates (e.g. retina displays)
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    // Setup viewport, orthographic projection matrix
    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render command lists
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
        const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
        glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
        glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer);
            }
            idx_buffer += pcmd->ElemCount;
        }
    }
#undef OFFSETOF

    // Restore modified state
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
}

void PassiveMotion(int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);
}

void MouseMotion(int x, int y)
{
    printf("mouse motion (%d, %d)\n", x, y);

    Viewport& vp = Module::sceneMan().getCamera()->getViewport();
    Matrix& viewMat = Module::sceneMan().getCamera()->getViewMatrix();
    if (gsMoveBtn == 1) // middle button, pan
    {
        viewMat = gsTmpMat;
        double dx, dy, dz;
        dx = (gsTmpX - x) / vp.pixScale;
        dy = (y - gsTmpY) / vp.pixScale;
        dz = 0;

        // transfer (dx, dy, dz) to world space
        double tmpX, tmpY, tmpZ;
        tmpX = viewMat.xx * dx + viewMat.yx * dy + viewMat.zx * dz + viewMat.xt;
        tmpY = viewMat.xy * dx + viewMat.yy * dy + viewMat.zy * dz + viewMat.yt;
        tmpZ = viewMat.xz * dx + viewMat.yz * dy + viewMat.zz * dz + viewMat.zt;

        dx = tmpX;
        dy = tmpY;
        dz = tmpZ;

        viewMat.xt = dx;
        viewMat.yt = dy;
        viewMat.zt = dz;
    }

    if (gsMoveBtn == 2) // right mouse button, rot
    {
        viewMat = gsTmpMat;

        double factor = 4.0 * (1.57079632679489661923 / vp.extent);
        double ang_y = factor * (gsTmpX - x) / vp.pixScale;
        double ang_x = factor * (gsTmpY - y) / vp.pixScale;

        Matrix& mat = viewMat;
        viewMat.rot(mat.yx, mat.yy, mat.yz, ang_y);
        viewMat.rot(mat.xx, mat.xy, mat.xz, ang_x);
    }

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)x, (float)y);

    glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y)
{
    if (state == 0)
    {
        gsMoveBtn = button;
        gsTmpX = x;
        gsTmpY = y;
        gsTmpMat = Module::sceneMan().getCamera()->getViewMatrix();
    }
    else
    {
        gsMoveBtn = -1;
    }

    if (button == 0 && state == 1)
    {
        Module::sceneMan().pick(x, y);
    }

    gsMousePressed[button] = true;

    printf("mouse button %d, %d, (%d, %d)\n", button, state, x, y);
    glutPostRedisplay();
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    printf("mouse wheel %d, %d, (%d, %d)\n", wheel, direction, x, y);

    Viewport& vp = Module::sceneMan().getCamera()->getViewport();
    double zoomFactor;
    zoomFactor = 1.0 + (160.0/(vp.extent*vp.pixScale)) * fabs((double)direction);

    if (direction > 0)
        vp.extent = vp.extent/zoomFactor;
    else
        vp.extent = vp.extent*zoomFactor;

    vp.pixScale = vp.pixHeight / vp.extent;

    glutPostRedisplay();
}

static void resize(int width, int height)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = (float)width;
    io.DisplaySize.y = (float)height;

    Module::sceneMan().getCamera()->getViewport().resize(width, height);
}

static void init(void)
{
    //imgui init
    ImGuiIO& io = ImGui::GetIO();
    io.RenderDrawListsFn = ImGuiRenderDrawLists;

    Module::init();

    skCreateScene1();

    std::unique_ptr<Effect> tmp(new EffectNormal);
    gsEffect = std::move(tmp);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    glDisable(GL_BLEND);

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
}

static void display(void)
{
//     glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//     glClearDepth(1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
//     gsEffect->render();
// 
//     if (!gsFontTexture)
//     {
//         ImGuiIO& io = ImGui::GetIO();
//         unsigned char* pixels;
//         int width, height;
//         io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);
// 
//         // Upload texture to graphics system
//         GLint last_texture;
//         glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
//         glGenTextures(1, &gsFontTexture);
//         glBindTexture(GL_TEXTURE_2D, gsFontTexture);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);
// 
//         // Store our identifier
//         io.Fonts->TexID = (void *)(intptr_t)gsFontTexture;
// 
//         // Restore state
//         glBindTexture(GL_TEXTURE_2D, last_texture);
//     }
// 
//     ImGuiIO& io = ImGui::GetIO();
// 
//     for (int i = 0; i < 3; i++)
//     {
//         io.MouseDown[i] = gsMousePressed[i] || gsMoveBtn == i;
//         gsMousePressed[i] = 0;
//     }
// 
//     ImGui::NewFrame();
// 
//     // deal with the event
//     if (gsEffectNormal)
//     {
//         std::unique_ptr<Effect> tmp(new EffectNormal);
//         gsEffect = std::move(tmp);
//         gsEffectNormal = false;
//     }
// 
//     if (gsEffectScreenTextureMap)
//     {
//         std::unique_ptr<Effect> tmp(new EffectTextureMap);
//         gsEffect = std::move(tmp);
//         gsEffectScreenTextureMap = false;
//     }
// 
//     if (gsEffectMotionBlur)
//     {
//         std::unique_ptr<Effect> tmp(new EffectMotionBlur);
//         gsEffect = std::move(tmp);
//         gsEffectMotionBlur = false;
//     }
// 
//     if (gsScene1)
//     {
//         skCreateScene1();
//         gsScene1 = false;
//     }
// 
//     if (gsScene2)
//     {
//         skCreateScene2();
//         gsScene2 = false;
//     }
// 
//     ImGuiWindowFlags window_flags = 0;
//     window_flags |= ImGuiWindowFlags_MenuBar;
//     bool opened = true;
//     if (ImGui::Begin("X", &opened, window_flags))
//     {
//         if (ImGui::BeginMenuBar())
//         {
//             if (ImGui::BeginMenu("Effects"))
//             {
//                 ImGui::MenuItem("Normal", NULL, &gsEffectNormal);
//                 ImGui::MenuItem("Screen Texture Map", NULL, &gsEffectScreenTextureMap);
//                 ImGui::MenuItem("Motion Blur", NULL, &gsEffectMotionBlur);
//                 ImGui::EndMenu();
//             }
//             if (ImGui::BeginMenu("Scene"))
//             {
//                 ImGui::MenuItem("Scene1", NULL, &gsScene1);
//                 ImGui::MenuItem("Scene2", NULL, &gsScene2);
//                 ImGui::EndMenu();
//             }
//             ImGui::EndMenuBar();
//         }
//     
//         if (ImGui::Button("Screenshot")) gsScreenshotButton ^= 1;
//         ImGui::End();
//     }
// 
//     if (gsScreenshotButton)
//     {
//         skScreenshot("123.bmp");
//         gsScreenshotButton ^= 1;
//     }
// 
//     ImGui::Render();

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

    bgfx::frame();

    glutSwapBuffers();
    glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q': glutLeaveMainLoop(); break;
    case 'r': Module::sceneMan().getCamera()->reset(); break;
    case 'z': Module::sceneMan().getCamera()->zoomAll(Module::sceneMan().boundingBox()); break;
    case '1': skScreenshot("123.bmp"); break;
    case 'p':
        {
            glm::mat4 vmat = Module::sceneMan().getCamera()->getViewMat();
            printf("%6.2f, %6.2f, %6.2f, %6.2f\n", vmat[0].x, vmat[1].x, vmat[2].x, vmat[3].x);
            printf("%6.2f, %6.2f, %6.2f, %6.2f\n", vmat[0].y, vmat[1].y, vmat[2].y, vmat[3].y);
            printf("%6.2f, %6.2f, %6.2f, %6.2f\n", vmat[0].z, vmat[1].z, vmat[2].z, vmat[3].z);
            printf("%6.2f, %6.2f, %6.2f, %6.2f\n", vmat[0].w, vmat[1].w, vmat[2].w, vmat[3].w);

            break;
        }
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(gsWinWidth, gsWinHeight);
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
    glutPassiveMotionFunc(PassiveMotion);
    glutMouseWheelFunc(MouseWheel);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    int test = ogl_LoadFunctions();
    if (test == ogl_LOAD_FAILED)
    {
        printf("err when glload init\n");
        return 1;
    }

    init();

    glutMainLoop();

    return 0;
}
