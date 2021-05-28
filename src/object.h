#pragma once

#include "ray.h"

struct Hit
{
    double t;
    Ray ray;
    Vec3 point;
    Vec3 normal;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};


class Object
{
public:
    virtual bool hit_test(const Ray&, double, double, Hit&) const = 0;     
};

