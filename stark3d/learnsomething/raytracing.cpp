#include "learnsomething.h"

#ifdef LEARN_RAYTRACING
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "utils/utils.h"
#include "utils/math.h"
#include "float.h"

using namespace SK;

Vec3f random_in_unit_sphere()
{
	Vec3f p;
	do {
		p = 2.0 * Vec3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX) - Vec3f(1, 1, 1);
	} while (p.length() >= 1.0);
	return p;
}

Vec3f reflect(const Vec3f& v, const Vec3f& n)
{
	return v - 2 * dot(v, n) * n;
}

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

class Material;
struct HitRecord 
{
    float t;
    Vec3f p;
    Vec3f normal;
	Material* mat_ptr;
};

class Material
{
public:
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3f& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const Vec3f & a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3f& attenuation, Ray& scattered) const
	{
		Vec3f target = rec.normal + random_in_unit_sphere();
		scattered = Ray(rec.p, target);
		attenuation = albedo;
		return true;
	}
		
	Vec3f albedo;
};

class Metal : public Material
{
public:
	Metal(const Vec3f & a, float f) : albedo(a), fuzz(f) {}
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3f& attenuation, Ray& scattered) const
	{
		Vec3f dir = r_in.direction();
		Vec3f reflected = reflect(dir.normalized(), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

	Vec3f albedo;
	float fuzz;
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
    Sphere(Vec3f cen, float r, Material* m) : center(cen), radius(r), mat_ptr(m) {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
    Vec3f center;
    float radius;
	Material *mat_ptr;
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
			rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
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

Vec3f color(const Ray& r, Hitable *world, int depth)
{
    HitRecord rec;
    if (world->hit(r, 0.0, FLT_MAX, rec))
    {
		Ray scattered;
		Vec3f attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3f(0, 0, 0);
		}
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

    Hitable* list[4];
    list[0] = new Sphere(Vec3f(0, 0, -1), 0.5, new Lambertian(Vec3f(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vec3f(0, -100.5, -1), 100, new Lambertian(Vec3f(0.8, 0.8, 0.0)));
	list[2] = new Sphere(Vec3f(1, 0, -1), 0.5, new Metal(Vec3f(0.8, 0.6, 0.2), 0.3));
	list[3] = new Sphere(Vec3f(-1, 0, -1), 0.5, new Metal(Vec3f(0.8, 0.8, 0.8), 1.0));
    Hitable* world = new HitableList(list, 4);

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
                col += color(r, world, 0);
            }
            col /= float(ns);
			col = Vec3f(sqrt(col.x), sqrt(col.y), sqrt(col.z));

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