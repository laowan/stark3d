#pragma once

#include <QDockWidget>
#include <windows.h>

#include "GL/glew.h"
#include "GL/wglew.h"

namespace SkEditor
{
    class RenderPanel : public QDockWidget
    {
        Q_OBJECT
    public:
        RenderPanel(QWidget* parent = 0);
        ~RenderPanel();
        void init();
        bool setupGL();
        bool destroyGL();

    public slots:
        void render();

    private:
        HWND _hWindow = NULL;
        HGLRC _hRC = NULL;
        HDC _hDC = NULL;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        GLuint ShaderProgram;
    };
}