#pragma once

#include "types.h"
#include "ray.h"

class Camera
{
public:
    Camera(double aspect_u, double aspect_v): aspect_u(aspect_u), aspect_v(aspect_v)
    {
        lower_left = Vec3{-aspect_u/2.0, -aspect_v/2.0, -1.0};
    }

    Ray get_ray(double u, double v){
        return Ray{ m_origin, lower_left + Vec3{u*aspect_u , v*aspect_v, 0.0}};
    }

private:
    Vec3 m_origin{0.0,0.0,0.0};
    Vec3 lower_left;
    double aspect_u;
    double aspect_v;
};
