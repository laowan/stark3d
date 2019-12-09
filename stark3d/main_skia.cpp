#include <stdio.h>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "include/core/SkFont.h"
#include "include/core/SkSurface.h"
#include "include/gpu/GrContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "src/gpu/gl/GrGLUtil.h"

#include "utils/utils.h"

//using namespace SK;

const int gsWinWidth = 800;
const int gsWinHeight = 600;

sk_sp<const GrGLInterface> fBackendContext;
sk_sp<GrContext> fContext;
sk_sp<SkSurface> fSurface;

static void init(void)
{
    fBackendContext = GrGLMakeNativeInterface();
    GrContextOptions defaultOptions;
    fContext = GrContext::MakeGL(fBackendContext, defaultOptions);

    GrGLint buffer;
    GR_GL_CALL(fBackendContext.get(), GetIntegerv(GR_GL_FRAMEBUFFER_BINDING, &buffer));

    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = buffer;
    fbInfo.fFormat = GR_GL_RGBA8;

    GrBackendRenderTarget backendRT(gsWinWidth, gsWinHeight, 1, 8, fbInfo);

    SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);
    fSurface = SkSurface::MakeFromBackendRenderTarget(fContext.get(), backendRT,
        kBottomLeft_GrSurfaceOrigin,
        kRGBA_8888_SkColorType,
        nullptr,
        &props);
}

static void exit(void)
{
    
}

static void displayClock(SkCanvas& canvas)
{
    float _strokeWidth = 8;
    int hour = 0;
    int minu = 0;
    int sec = 0;

    time_t now = time(0);
    tm* t = localtime(&now);
    hour = t->tm_hour;
    minu = t->tm_min;
    sec = t->tm_sec;

    canvas.save();
    canvas.clear(SK_ColorWHITE);
    
    canvas.translate(200, 200);
    canvas.scale(1, 1);
    canvas.rotate(-90);
    
    SkPaint paint;
    paint.setColor(SK_ColorBLUE);
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(_strokeWidth);
    paint.setStrokeCap(SkPaint::kRound_Cap);
    //paint.setAntiAlias(_antiAlias);
    
    // hour marks
    canvas.save();
    for (int i = 1; i <= 12; i++)
    {
        canvas.rotate(30);
        SkPath path;
        path.moveTo(100, 0);
        path.lineTo(120, 0);
        canvas.drawPath(path, paint);
    }
    canvas.restore();

    // minute marks
    paint.setStrokeWidth(_strokeWidth / 1.5);
    canvas.save();
    for (int i = 0; i <= 59; i++)
    {
        if (i % 5 != 0)
        {
            SkPath path;
            path.moveTo(115, 0);
            path.lineTo(120, 0);
            canvas.drawPath(path, paint);
        }
        canvas.rotate(6);
    }
    canvas.restore();
    
    // write hour
    {
        paint.setStrokeWidth(_strokeWidth * 2);
        canvas.save();
        canvas.rotate(hour * 30 + 0.5 * minu + 180.0 / 21600 * sec);
        SkPath path;
        path.moveTo(-20, 0);
        path.lineTo(80, 0);
        canvas.drawPath(path, paint);
        canvas.restore();
    }
    
    // write minutes
    {
        paint.setStrokeWidth(_strokeWidth);
        canvas.save();
        canvas.rotate(6 * minu + 180.0 / 1800 * sec);
        SkPath path;
        path.moveTo(-28, 0);
        path.lineTo(112, 0);
        canvas.drawPath(path, paint);
        canvas.restore();
    }
    
    // write second
    {
        paint.setStrokeWidth(_strokeWidth / 2);
        canvas.save();
        canvas.rotate(6 * sec);
        SkPath path;
        path.moveTo(-30, 0);
        path.lineTo(83, 0);
        canvas.drawPath(path, paint);
        canvas.restore();
    }

    canvas.restore();
}

static void displayParticle(SkCanvas& canvas)
{
    canvas.save();

    // Clear background
    canvas.clear(SK_ColorWHITE);

    SkPaint paint;
    paint.setColor(SK_ColorRED);
    //paint.setStrokeWidth(5);
    //paint.setStyle(SkPaint::kStroke_Style);
    //paint.setAntiAlias(true);

    SkPath path;
    float radius = 10;
    float gap = 10;
    float startx = 0, starty = 0;

    float x, y;
    for (int i = 1; i <= 50; i++)
    {
        y = starty + (2 * radius + gap) * (i - 1);
        for (int j = 1; j <= 20; j++)
        {
            x = startx + (2 * radius + gap) * (j - 1);
            path.addCircle(x, y, radius);
        }
    }
    canvas.drawPath(path, paint);
    canvas.restore();
}

static void display_skia(void)
{
    //glClearColor(1.0, 0.0, 0.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    SKUInt64 startTime = CurrentTime();

    fContext->resetContext();
    auto canvas = fSurface->getCanvas();

    displayClock(*canvas);
    //displayParticle(*canvas);

//     canvas->save();
//     canvas->clear(SK_ColorWHITE);
//     canvas->translate(128, 0);
//     canvas->rotate(60);
// 
//     SkPaint paint;
//     paint.setColor(SK_ColorBLUE);
//     //paint.setAntiAlias(true);
// 
//     SkRect rect = SkRect::MakeXYWH(0, 0, 200, 100);
//     canvas->drawRect(rect, paint);
// 
//     canvas->restore();

    SkFont font;
    font.setSize(50);
    SkPaint paint;
    paint.setColor(SK_ColorBLACK);
    paint.setStyle(SkPaint::kStroke_Style);

    static const char message[] = "Hello World";
    canvas->drawSimpleText(message, strlen(message), SkTextEncoding::kUTF8, 0, 200, font, paint);

    fSurface->flush();

    glFinish();
    std::cout << "cpu time : " << CurrentTime() - startTime << std::endl;
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

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        display_skia();

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
