#ifndef UTILS_MATRIX_H
#define UTILS_MATRIX_H

#include <glm/glm.hpp>

namespace Util
{

class Matrix
{
public:
    Matrix();
    ~Matrix();

    glm::mat4 glMatrix();

    void rot(double kx, double ky, double kz, double theta);
    Matrix mul(Matrix& mat);

public:
    double xx, yx, zx, xt;
    double xy, yy, zy, yt;
    double xz, yz, zz, zt;
};

}

#endif