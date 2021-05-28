#pragma once

#include "types.h"
#include "utils.h"
#include "object.h"

class Material
{
public:
    virtual bool scatter(const Ray& ray_in, const Hit& hit, color& attenuation, Ray& scattered) const = 0;
};

class Diffuse : public Material {
public:
    Diffuse(color c) : albedo(c) {}

    virtual bool scatter(const Ray& ray_in, const Hit& hit, color& attenuation, Ray& scattered) const override
    {
        scattered = Ray{ hit.point, random_vec3_in_hemisphere(hit.normal) };
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
};

class Metal : public Material {
public:
    Metal(color c, double fuzz) : albedo(c), fuzz(fuzz) {}

    virtual bool scatter(const Ray& ray_in, const Hit& hit, color& attenuation, Ray& scattered) const override
    {

        Vec3 reflected = reflect(ray_in.direction(), hit.normal) + random_vec3_in_sphere() * fuzz;
        scattered = Ray{ hit.point, reflected };
        attenuation = albedo;
        return (dot(scattered.direction(), hit.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};