#pragma once

#include <random>
#include "glm/glm.hpp"

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

Vec3 random_vec3() {
    return Vec3{ random_double(), random_double(), random_double() };
}
Vec3 random_vec3(double min, double max) {
    return Vec3{ random_double(min, max), random_double(min, max), random_double(min, max) };
}

Vec3 random_unit_vec3(){
    return glm::normalize(random_vec3(-1.0, 1.0)); 
}

Vec3 random_vec3_in_sphere() {
    while (true) {
        auto p = random_vec3(-1.0,1.0);
        if (length2(p) >= 1) continue;
        return p;
    }
}

Vec3 random_vec3_in_hemisphere(const Vec3& normal){
    Vec3 in_unit_sphere = random_unit_vec3();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}