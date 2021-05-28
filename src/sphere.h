#pragma once

#include "types.h"
#include "object.h"

class Sphere : public Object
{
private:
    Vec3 m_center;
    double m_radius;
    std::shared_ptr<Material> m_material;
public:
    Sphere(Vec3 center, float radius, std::shared_ptr<Material> material): 
    m_center(center), m_radius(radius), m_material(material)
    {}
    Vec3 center() const{
        return m_center;
    }
    double radius() const{
        return m_radius;
    }

    bool hit_test(const Ray& ray, double t_min, double t_max, Hit& hit) const override{
        Vec3 oc = ray.origin() - m_center;
        auto a = length2(ray.direction());
        auto half_b = dot(oc, ray.direction());
        auto c = length2(oc) - m_radius*m_radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }
        hit.t = root;
        hit.point = ray.at(hit.t);
        hit.material = m_material;
        Vec3 outward_normal = (hit.point - m_center) / m_radius;
        hit.set_face_normal(ray, outward_normal);

        return true;
    }
};
