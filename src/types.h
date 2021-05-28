#pragma once

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/glm.hpp"
#include <limits>

using color = glm::dvec4;
using Vec3 = glm::dvec3;

double length2(const Vec3& v){
    return dot(v,v);
}

const double Inf = std::numeric_limits<double>::infinity();