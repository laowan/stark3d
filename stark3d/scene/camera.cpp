#include "camera.h"

SK_BEGIN_NAMESPACE

Camera::Camera()
{}

Camera::~Camera()
{}

glm::mat4 Camera::getViewProjMat()
{
    // mat is the inverse matrix of _viewMat
    // from world coordinate to view coordinate
    Matrix mat;
    mat.xx = _viewMat.xx; mat.yx = _viewMat.xy; mat.zx = _viewMat.xz;
    mat.xy = _viewMat.yx; mat.yy = _viewMat.yy; mat.zy = _viewMat.yz;
    mat.xz = _viewMat.zx; mat.yz = _viewMat.zy; mat.zz = _viewMat.zz;

    mat.xt = -_viewMat.xx*_viewMat.xt - _viewMat.xy*_viewMat.yt - _viewMat.xz*_viewMat.zt;
    mat.yt = -_viewMat.yx*_viewMat.xt - _viewMat.yy*_viewMat.yt - _viewMat.yz*_viewMat.zt;
    mat.zt = -_viewMat.zx*_viewMat.xt - _viewMat.zy*_viewMat.yt - _viewMat.zz*_viewMat.zt;

    mat.zt -= 100.0f;

    glm::mat4 mvMat = mat.glMatrix();
    glm::mat4 projMat = getOrthographicProjMat();
    glm::mat4 mvpMat = projMat * mvMat;

    return mvpMat;
}

glm::mat4 Camera::getPerspectiveProjMat()
{
    // http://www.songho.ca/opengl/gl_projectionmatrix.html
    glm::mat4 mat;
    double h_w = (double)_viewport._pixHeight /_viewport._pixWidth;
    double r, t;

    if (h_w > 1.0)
    {
        r = _viewport._extent / 2.0;
        t = _viewport._extent * h_w / 2.0;
    }
    else
    {
        r = _viewport._extent / h_w / 2.0;
        t = _viewport._extent / 2.0;
    }

    float n = 100.0, f = -100.0;
    mat[0].x = n / r; mat[1].x = 0.0;   mat[2].x = 0.0;         mat[3].x = 0.0;
    mat[0].y = 0.0;   mat[1].y = n / t; mat[2].y = 0.0;         mat[3].y = 0.0;
    mat[0].z = 0.0;   mat[1].z = 0.0;   mat[2].z = (f + n) / (n - f); mat[3].z = 2 * f*n / (n - f);
    mat[0].w = 0.0;   mat[1].w = 0.0;   mat[2].w = -1.0;        mat[3].w = 0.0;
    return mat;
}

glm::mat4 Camera::getOrthographicProjMat()
{
    /*
        n is the distance from view origin to front clip plane.
        f is the distance form view origin to back clip plane.
    */
    glm::mat4 mat;
    double h_w = (double)_viewport._pixHeight /_viewport._pixWidth;
    double r, t;

    if (h_w > 1.0)
    {
        r = _viewport._extent / 2.0;
        t = _viewport._extent * h_w / 2.0;
    }
    else
    {
        r = _viewport._extent / h_w / 2.0;
        t = _viewport._extent / 2.0;
    }

    float n = 1.0, f = 200.0;
    mat[0].x = 1.0/r; mat[1].x = 0.0;   mat[2].x = 0.0;       mat[3].x = 0.0;
    mat[0].y = 0.0;   mat[1].y = 1.0/t; mat[2].y = 0.0;       mat[3].y = 0.0;
    mat[0].z = 0.0;   mat[1].z = 0.0;   mat[2].z = 2.0/(n-f); mat[3].z = (f+n)/(n-f);
    mat[0].w = 0.0;   mat[1].w = 0.0;   mat[2].w = 0.0;       mat[3].w = 1.0;
    return mat;
}

void Camera::reset()
{
    _viewMat = Matrix();
}

SK_END_NAMESPACE
