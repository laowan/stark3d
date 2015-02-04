#ifndef COLOR_H
#define COLOR_H

#include "scene.h"

namespace Scene
{

class Color : public SceneNode
{
public:
    Color(double r, double g, double b, double a);
    Color(float r, float g, float b, float a);
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    bool render();

private:
    float _r;
    float _g;
    float _b;
    float _a;
};

}

#endif
