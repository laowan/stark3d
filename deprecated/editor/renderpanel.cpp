#include "renderpanel.h"

#include <iostream>



namespace SkEditor
{
    void PrintOpenGLErrors(char const * const Function, char const * const File, int const Line)
    {
        bool Succeeded = true;

        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
        {
            char const * ErrorString = (char const *)gluErrorString(Error);
            if (ErrorString)
                std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%s'", File, Line, Function, ErrorString) << std::endl;
            else
                std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%d 0x%X'", File, Line, Function, Error, Error) << std::endl;
        }
    }

#ifdef _DEBUG
#define CheckedGLCall(x) do { PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__); (x); PrintOpenGLErrors(#x, __FILE__, __LINE__); } while (0)
#define CheckedGLResult(x) (x); PrintOpenGLErrors(#x, __FILE__, __LINE__);
#define CheckExistingErrors(x) PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__);
#else
#define CheckedGLCall(x) (x)
#define CheckExistingErrors(x)
#endif


    void PrintShaderInfoLog(GLint const Shader)
    {
        int InfoLogLength = 0;
        int CharsWritten = 0;

        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);

        if (InfoLogLength > 0)
        {
            GLchar * InfoLog = new GLchar[InfoLogLength];
            glGetShaderInfoLog(Shader, InfoLogLength, &CharsWritten, InfoLog);
            std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
            delete[] InfoLog;
        }
    }

    RenderPanel::RenderPanel(QWidget* parent)
        : QDockWidget(parent)
    {
        setWindowTitle("Preview");
    }

    RenderPanel::~RenderPanel()
    {

    }

    bool RenderPanel::setupGL()
    {
        _hWindow = (HWND)winId();
        _hDC = ::GetDC(_hWindow);
        if (_hDC == NULL)
        {
            return false;
        }

        int nPixelFormat;
        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),    // Size of this structure
            1,                                // Version of this structure    
            PFD_DRAW_TO_WINDOW |              // Draw to Window (not to bitmap)
            PFD_SUPPORT_OPENGL |              // Support OpenGL calls in window
            PFD_DOUBLEBUFFER,                 // Double buffered mode
            PFD_TYPE_RGBA,                    // RGBA Color mode
            32,                               // Want 32 bit color 
            0, 0, 0, 0, 0, 0,                 // Not used to select mode
            0, 0,                             // Not used to select mode
            0, 0, 0, 0, 0,                    // Not used to select mode
            16,                               // Size of depth buffer
            0,                                // Not used 
            0,                                // Not used 
            0,                                // Not used 
            0,                                // Not used 
            0, 0, 0 };                         // Not used 

        //
        // Choose a pixel format that best matches that described in pfd
        //
        nPixelFormat = ::ChoosePixelFormat(_hDC, &pfd);

        if (nPixelFormat == 0)
        {
            DWORD errorCode = ::GetLastError();
            printf("ChoosePixelFormat ErrorCode: %u", errorCode);

            ::ReleaseDC(_hWindow, _hDC);
            return false;
        }

        //
        // Set the pixel format for the device context
        //
        BOOL bSet = ::SetPixelFormat(_hDC, nPixelFormat, &pfd);
        if (bSet == FALSE)
        {
            ::ReleaseDC(_hWindow, _hDC);
            return false;
        }

        //
        // Create OGL context and make it current
        //
        HGLRC tempRC = ::wglCreateContext(_hDC);
        if (tempRC == NULL)
        {
            DWORD errorCode = GetLastError();
            printf("wglCreateContext ErrorCode: %u", errorCode);

            ::ReleaseDC(_hWindow, _hDC);
            return false;
        }

        BOOL bMake = ::wglMakeCurrent(_hDC, tempRC);
        if (bMake == FALSE)
        {
            DWORD errorCode = ::GetLastError();
            printf("wglMakeCurrent ErrorCode: %u", errorCode);

            ::wglDeleteContext(tempRC);
            ::ReleaseDC(_hWindow, _hDC);
            return false;
        }

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            printf("glewInit ErrorCode: %u", err);
        }

        int attriblist[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 0, 0 };

        //
        // Create OGL context and make it current
        //
        _hRC = wglCreateContextAttribsARB(_hDC, 0, attriblist);
        if (_hRC == NULL)
        {
            DWORD errorCode = GetLastError();
            printf("wglCreateContextAttribsARB ErrorCode: %u", errorCode);

            ::ReleaseDC(_hWindow, _hDC);
            return false;
        }

        wglDeleteContext(tempRC);
        bMake = wglMakeCurrent(_hDC, _hRC);
        if (bMake == FALSE)
        {
            DWORD errorCode = ::GetLastError();
            printf("wglMakeCurrent ErrorCode: %u", errorCode);

            ::wglDeleteContext(_hRC);
            ::ReleaseDC(_hWindow, _hDC);
            return false;
        }

        glClearDepth(1.0f);
        return true;
    }

    bool RenderPanel::destroyGL()
    {
        ::wglMakeCurrent(NULL, NULL);
        if (_hRC)
        {
            ::wglDeleteContext(_hRC);
            _hRC = NULL;
        }

        if (_hDC)
        {
            ::ReleaseDC(_hWindow, _hDC);
            _hDC = NULL;
        }
        return true;
    }

    void RenderPanel::init()
    {
        setupGL();

        char const * VertexShaderSource = R"GLSL(
		#version 150
		in vec2 position;
		void main()
		{
			gl_Position = vec4(position, 0.0, 1.0);
		}
	)GLSL";

        char const * FragmentShaderSource = R"GLSL(
		#version 150
		out vec4 outColor;
		void main()
		{
			outColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
	)GLSL";

        GLfloat const Vertices[] = {
            0.0f, 0.5f,
            0.5f, -0.5f,
            -0.5f, -0.5f
        };

        GLuint const Elements[] = {
            0, 1, 2
        };

        //GLuint VAO;
        CheckedGLCall(glGenVertexArrays(1, &VAO));
        CheckedGLCall(glBindVertexArray(VAO));

        //GLuint VBO;
        CheckedGLCall(glGenBuffers(1, &VBO));
        CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW));
        CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        //GLuint EBO;
        CheckedGLCall(glGenBuffers(1, &EBO));
        CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
        CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW));

        GLint Compiled;
        GLuint VertexShader = CheckedGLResult(glCreateShader(GL_VERTEX_SHADER));
        CheckedGLCall(glShaderSource(VertexShader, 1, &VertexShaderSource, NULL));
        CheckedGLCall(glCompileShader(VertexShader));
        CheckedGLCall(glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Compiled));
        if (!Compiled)
        {
            std::cerr << "Failed to compile vertex shader!" << std::endl;
            PrintShaderInfoLog(VertexShader);
        }

        GLuint FragmentShader = CheckedGLResult(glCreateShader(GL_FRAGMENT_SHADER));
        CheckedGLCall(glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL));
        CheckedGLCall(glCompileShader(FragmentShader));
        CheckedGLCall(glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Compiled));
        if (!Compiled)
        {
            std::cerr << "Failed to compile fragment shader!" << std::endl;
            PrintShaderInfoLog(FragmentShader);
        }

        ShaderProgram = CheckedGLResult(glCreateProgram());
        CheckedGLCall(glAttachShader(ShaderProgram, VertexShader));
        CheckedGLCall(glAttachShader(ShaderProgram, FragmentShader));
        CheckedGLCall(glBindFragDataLocation(ShaderProgram, 0, "outColor"));
        CheckedGLCall(glLinkProgram(ShaderProgram));
        CheckedGLCall(glUseProgram(ShaderProgram));
    }

    void RenderPanel::render()
    {
        QSize sz = size();
        glViewport(0, 0, sz.width(), sz.height());

        CheckedGLCall(glUseProgram(ShaderProgram));
        GLint PositionAttribute = CheckedGLResult(glGetAttribLocation(ShaderProgram, "position"));
        CheckedGLCall(glEnableVertexAttribArray(PositionAttribute));

        CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        CheckedGLCall(glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0));
        CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        glClearColor(0.5, 0.5, 0.5, 1.0);
        CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        CheckedGLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));

        ::SwapBuffers(_hDC);
    }
}