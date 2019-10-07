#include "learnsomething.h"

#ifdef LEARN_RAYTRACING
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "utils/utils.h"
#include "utils/math.h"
#include "float.h"

using namespace SK;

class Ray
{
public:
    Ray() {}
    Ray(const Vec3f& a, const Vec3f& b) { A = a; B = b; }
    Vec3f origin() const { return A; }
    Vec3f direction() const { return B; }
    Vec3f point_at_parameter(float t) const { return A + B * t; }

    Vec3f A;
    Vec3f B;
};

class Camera
{
public:
    Camera()
    {
        lower_left_corner = Vec3f(-2.0, -1.0, -1.0);
        horizontal = Vec3f(4.0, 0.0, 0.0);
        vertical = Vec3f(0.0, 2.0, 0.0);
        origin = Vec3f(0.0, 0.0, 0.0);
    }
    Ray getRay(float u, float v) { return Ray(origin, lower_left_corner + u * horizontal + v * vertical); }
    Vec3f origin;
    Vec3f lower_left_corner;
    Vec3f horizontal;
    Vec3f vertical;
};

struct HitRecord 
{
    float t;
    Vec3f p;
    Vec3f normal;
};

class Hitable 
{
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

class Sphere : public Hitable
{
public:
    Sphere() {}
    Sphere(Vec3f cen, float r) : center(cen), radius(r) {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
    Vec3f center;
    float radius;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    Vec3f oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

class HitableList : public Hitable
{
public:
    HitableList() {}
    HitableList(Hitable **l, int n) { list = l; listSize = n; }
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
    Hitable **list;
    int listSize;
};

bool HitableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    HitRecord tempRec;
    bool hitAnything = false;
    double closest = t_max;
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->hit(r, t_min, closest, tempRec))
        {
            hitAnything = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}

Vec3f color(const Ray& r, Hitable *world)
{
    HitRecord rec;
    if (world->hit(r, 0.0, FLT_MAX, rec))
    {
        return 0.5 * Vec3f(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
    }
    else
    {
        Vec3f unit_direction = r.direction().normalized();
        float t = 0.5 * (unit_direction.y + 1.0);
        return Vec3f(1.0, 1.0, 1.0) * (1.0 - t) + Vec3f(0.5, 0.7, 1.0) * t;
    }
}

void LearnRayTracing()
{
    const char* outPath = "../res/HYQuHeiW.ttf";

    int nx = 200;
    int ny = 100;
    int ns = 100;
    unsigned char* data = new unsigned char[nx * ny * 3];

    Camera cam;

    Hitable* list[2];
    list[0] = new Sphere(Vec3f(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3f(0, -100.5, -1), 100);
    Hitable* world = new HitableList(list, 2);

    for (int j = 0; j < ny; j++)
    {
        for (int i = 0; i < nx; i++)
        {
            Vec3f col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + (float)rand() / RAND_MAX) / float(nx);
                float v = float(j + (float)rand() / RAND_MAX) / float(ny);
                Ray r = cam.getRay(u, v);
                col += color(r, world);
            }
            col /= float(ns);

            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);

            data[(ny - j - 1) * nx * 3 + i * 3 + 0] = ir;
            data[(ny - j - 1) * nx * 3 + i * 3 + 1] = ig;
            data[(ny - j - 1) * nx * 3 + i * 3 + 2] = ib;
        }
    }

    stbi_write_bmp("x.bmp", nx, ny, 3, data);

    delete[] data;
}

#endif