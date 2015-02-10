#ifndef UTILS_MATRIX_H
#define UTILS_MATRIX_H

#include "global.h"
#include <glm/glm.hpp>

SK_BEGIN_NAMESPACE

class Matrix
{
public:
    Matrix();
    ~Matrix();

    glm::mat4 glMatrix();

    void pan(double x, double y, double z);
    void rot(double kx, double ky, double kz, double theta);
    Matrix mul(Matrix& mat);

public:
    double xx, yx, zx, xt;
    double xy, yy, zy, yt;
    double xz, yz, zz, zt;
};

SK_END_NAMESPACE

#endif
