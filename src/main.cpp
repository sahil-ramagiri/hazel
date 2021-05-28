/*
 *  Copyright (c) 2021, Sahil Kumar. <https://github.com/sahil-ramagiri>
 *
 *  Licensed under the MIT License.
 */

#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include <memory>
#include "types.h"
#include "frame_buffer.h"
#include "camera.h"
#include "sphere.h"
#include "renderer.h"


int main()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::stopwatch sw;

    const auto aspect_ratio = 16.0 / 9.0;
    const size_t image_width = 400;
    const size_t image_height = static_cast<size_t>(image_width / aspect_ratio);

    FrameBuffer fb{ image_width, image_height };
    Camera cam{2.0 * aspect_ratio, 2.0};
    auto sphere = std::make_shared<Sphere>(Vec3{0.0,0.0,-1.0}, 0.5);
    auto plane = std::make_shared<Sphere>(Vec3{0.0,-100.5,-1.0}, 100.0);
    Scene scene{};
    scene.add(sphere);
    scene.add(plane);
    // Render
    render(scene, cam, fb);
    fb.dump_to_file("test.png");
    spdlog::debug("That took {:.3}s", sw);
    return 0;
}