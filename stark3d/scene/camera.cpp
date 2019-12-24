#include "camera.h"
#include "string.h"

SK_BEGIN_NAMESPACE

Camera::Camera()
{}

Camera::~Camera()
{}

void Camera::getViewMat(mat4x4 mat)
{
    mat4x4_look_at(mat, _eye, _target, _up);
}

void Camera::getProjMat(mat4x4 mat)
{
    mat4x4_dup(mat, _projMat);
}

void Camera::setPerspective(float fov, float aspect, float n, float f)
{
    mat4x4_perspective(_projMat, fov, aspect, n, f);
}

void Camera::setLookAt(vec3 eye, vec3 target, vec3 up)
{
    memcpy(_eye, eye, sizeof(vec3));
    memcpy(_target, target, sizeof(vec3));
    memcpy(_up, up, sizeof(vec3));
}

void Camera::getPerspectiveProjMat(mat4x4 mat)
{
    // http://www.songho.ca/opengl/gl_projectionmatrix.html
    double h_w = (double)_viewport.pixHeight /_viewport.pixWidth;
    double r, t;

    if (h_w > 1.0)
    {
        r = _viewport.extent / 2.0;
        t = _viewport.extent * h_w / 2.0;
    }
    else
    {
        r = _viewport.extent / h_w / 2.0;
        t = _viewport.extent / 2.0;
    }

    float n = 100.0, f = -100.0;
    mat[0][0] = n / r; mat[1][0] = 0.0;   mat[2][0] = 0.0;         mat[3][0] = 0.0;
    mat[0][1] = 0.0;   mat[1][1] = n / t; mat[2][1] = 0.0;         mat[3][1] = 0.0;
    mat[0][2] = 0.0;   mat[1][2] = 0.0;   mat[2][2] = (f + n) / (n - f); mat[3][2] = 2 * f*n / (n - f);
    mat[0][3] = 0.0;   mat[1][3] = 0.0;   mat[2][3] = -1.0;        mat[3][3] = 0.0;
}

void Camera::getOrthographicProjMat(mat4x4 mat)
{
    /*
        n is the distance from view origin to front clip plane.
        f is the distance form view origin to back clip plane.
    */
    double h_w = (double)_viewport.pixHeight /_viewport.pixWidth;
    double r, t;

    if (h_w > 1.0)
    {
        r = _viewport.extent / 2.0;
        t = _viewport.extent * h_w / 2.0;
    }
    else
    {
        r = _viewport.extent / h_w / 2.0;
        t = _viewport.extent / 2.0;
    }

    float n = 1.0, f = 200.0;
    mat[0][0] = 1.0/r; mat[1][0] = 0.0;   mat[2][0] = 0.0;       mat[3][0] = 0.0;
    mat[0][1] = 0.0;   mat[1][1] = 1.0/t; mat[2][1] = 0.0;       mat[3][1] = 0.0;
    mat[0][2] = 0.0;   mat[1][2] = 0.0;   mat[2][2] = 2.0/(n-f); mat[3][2] = (f+n)/(n-f);
    mat[0][3] = 0.0;   mat[1][3] = 0.0;   mat[2][3] = 0.0;       mat[3][3] = 1.0;
}

SK_END_NAMESPACE
