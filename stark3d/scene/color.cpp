#include "color.h"

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

bool Color::render(RenderAction* act)
{
    act->_color = glm::vec4(_r, _g, _b, _a);
    return true;
}

SK_END_NAMESPACE
