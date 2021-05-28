#pragma once

#include "frame_buffer.h"
#include "scene.h"
#include "camera.h"
#include "utils.h"

color shade(const Ray& ray, Scene& scene, size_t depth) {

    if (depth <= 0 ){
        return color(0.0);
    }
    Hit hit;
    if (scene.get_hit(ray, 0.001, Inf, hit)) {
        color attenuation;
        Ray scattered;
        if (hit.material->scatter(ray, hit, attenuation, scattered))
            return attenuation * shade(scattered, scene, depth-1);
        return color(0.0);
    }
    // world/sky color 
    auto t = 0.5 * (ray.direction().y + 1.0);
    return (1.0 - t) * color(1.0) + t * color(0.5, 0.7, 1.0, 1.0);
}


void render(Scene& scene, Camera& camera, FrameBuffer& fb) {
    const size_t num_samples = 100;
    const size_t max_light_bounces = 50;
    auto scale = (1.0 / num_samples);
#pragma omp parallel for
    for (int row = 0; row < fb.height(); row++) {
        for (int col = 0; col < fb.width(); col++) {
            color color_val(0.0);
            for (int s = 0; s < num_samples;s++) {
                auto u = double(col + random_double()) / (fb.width() - 1);
                auto v = double(row + random_double()) / (fb.height() - 1);
                auto ray = camera.get_ray(u, v);
                color_val += shade(ray, scene, max_light_bounces);
            }
            color_val *= scale;
            fb.set_pixel(fb.height() - row - 1, col, color_val);
        }
    }
}