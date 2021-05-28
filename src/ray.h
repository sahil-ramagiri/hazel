#pragma once

#include "glm/glm.hpp"
#include "types.h"

class Ray
{

public:
    Ray() {}
    Ray(const Vec3& origin, const Vec3& direction) :
        m_origin(origin), m_direction(glm::normalize(direction)) {}

    const Vec3& origin() const {
        return m_origin;
    }
    const Vec3& direction() const {
        return m_direction;
    }

    Vec3 at(double t) const{
        return m_origin + m_direction * t;
    }

private:
    Vec3 m_origin;
    Vec3 m_direction;
};
