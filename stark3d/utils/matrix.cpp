#include "matrix.h"

SK_BEGIN_NAMESPACE

Matrix::Matrix()
{
    xx = 1, yx = 0, zx = 0, xt = 0;
    xy = 0, yy = 1, zy = 0, yt = 0;
    xz = 0, yz = 0, zz = 1, zt = 0;
}

Matrix::~Matrix()
{

}

void Matrix::pan(double x, double y, double z)
{
    xt += x;
    yt += y;
    zt += z;
}

void Matrix::rot(double kx, double ky, double kz, double theta)
{
    double sint, cost, verst;
    Matrix m1;

    sint = sin(theta);
    cost = cos(theta);
    verst = 1.0 - cost;

    /* first row */
    m1.xx = kx * kx * verst + cost;
    m1.yx = ky * kx * verst - kz * sint;
    m1.zx = kz * kx * verst + ky * sint;
    m1.xt = 0.0;

    /* second row */
    m1.xy = kx * ky * verst + kz * sint;
    m1.yy = ky * ky * verst + cost;
    m1.zy = kz * ky * verst - kx * sint;
    m1.yt = 0.0;

    /* third row */
    m1.xz = kx * kz * verst - ky * sint;
    m1.yz = ky * kz * verst + kx * sint;
    m1.zz = kz * kz * verst + cost;
    m1.zt = 0.0;
    
    Matrix retMat = m1.mul(*this);
    *this = retMat;
}

//! the matrix's data is not changed.
Matrix Matrix::mul(Matrix& mat)
{
    Matrix retMat;
    retMat.xx = xx*mat.xx + yx*mat.xy + zx*mat.xz;
    retMat.xy = xy*mat.xx + yy*mat.xy + zy*mat.xz;
    retMat.xz = xz*mat.xx + yz*mat.xy + zz*mat.xz;

    retMat.yx = xx*mat.yx + yx*mat.yy + zx*mat.yz;
    retMat.yy = xy*mat.yx + yy*mat.yy + zy*mat.yz;
    retMat.yz = xz*mat.yx + yz*mat.yy + zz*mat.yz;

    retMat.zx = xx*mat.zx + yx*mat.zy + zx*mat.zz;
    retMat.zy = xy*mat.zx + yy*mat.zy + zy*mat.zz;
    retMat.zz = xz*mat.zx + yz*mat.zy + zz*mat.zz;

    retMat.xt = xx*mat.xt + yx*mat.yt + zx*mat.zt + xt;
    retMat.yt = xy*mat.xt + yy*mat.yt + zy*mat.zt + yt;
    retMat.zt = xz*mat.xt + yz*mat.yt + zz*mat.zt + zt;

    return retMat;
}

glm::mat4 Matrix::glMatrix()
{
    glm::mat4 mat;
    mat[0].x = (float)xx;  mat[1].x = (float)yx;  mat[2].x = (float)zx;  mat[3].x = (float)xt;
    mat[0].y = (float)xy;  mat[1].y = (float)yy;  mat[2].y = (float)zy;  mat[3].y = (float)yt;
    mat[0].z = (float)xz;  mat[1].z = (float)yz;  mat[2].z = (float)zz;  mat[3].z = (float)zt;
    mat[0].w = 0.0;        mat[1].w = 0.0;        mat[2].w = 0.0;        mat[3].w = 1.0;

    return mat;
}

SK_END_NAMESPACE
