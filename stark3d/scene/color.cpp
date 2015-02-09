#include "color.h"
#include "../module.h"
#include <glload/gl_3_3.h>

SK_BEGIN_NAMESPACE

Color::Color(double r, double g, double b, double a)
{
    _r = (float)r;
    _g = (float)g;
    _b = (float)b;
    _a = (float)a;
}

Color::Color(float r, float g, float b, float a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    _r = (float)(r / 255.0);
    _g = (float)(g / 255.0);
    _b = (float)(b / 255.0);
    _a = (float)(a / 255.0);
}

bool Color::render()
{
    ShaderUniforms& uniforms = Module::shaderMan().currentShader()->uniforms();

    float data[4];
    data[0] = _r;
    data[1] = _g;
    data[2] = _b;
    data[3] = _a;

    glUniform4fv(uniforms.color, 1, data);
    
    return true;
}

SK_END_NAMESPACE
