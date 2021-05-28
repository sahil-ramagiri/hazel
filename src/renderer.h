#pragma once

#include "frame_buffer.h"
#include "scene.h"
#include "camera.h"
#include <random>

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

color get_color(const Ray& ray, Scene& scene){
    Hit hit;
    if (scene.get_hit(ray,0.0, Inf ,hit)){
        auto N = hit.normal;
        return 0.5*color(N.x+1, N.y+1, N.z+1, 2.0);
    }
    auto t = 0.5*(ray.direction().y + 1.0);
    return (1.0-t)*color(1.0) + t*color(0.5, 0.7, 1.0, 1.0);
}


void render(Scene& scene, Camera& camera, FrameBuffer& fb, size_t samples = 100){
    auto scale = (1.0 / samples);
    #pragma omp parallel for
    for (int row = 0; row < fb.height(); row++) {
        for (int col = 0; col < fb.width(); col++) {
            color color_val(0.0);
            for (int s=0; s<samples;s++){
                auto u = double(col + random_double()) / (fb.width()-1);
                auto v = double(row + random_double()) / (fb.height()-1);
                auto ray = camera.get_ray(u, v);
                color_val += get_color(ray, scene);
            }
            fb.set_pixel(fb.height() - row - 1, col, color_val * scale);
        }
    }
}