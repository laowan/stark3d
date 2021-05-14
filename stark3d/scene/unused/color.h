#ifndef COLOR_H
#define COLOR_H

#include "node.h"

SK_BEGIN_NAMESPACE

class STARK_API Color : public SceneNode
{
public:
    Color(double r, double g, double b, double a);
    Color(float r, float g, float b, float a);
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    std::string type() { return "Color"; }

    bool render(RenderAction* act);

private:
    float _r;
    float _g;
    float _b;
    float _a;
};

SK_END_NAMESPACE

#endif
