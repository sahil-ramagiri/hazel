/*
 *  Copyright (c) 2021, Sahil Kumar. <https://github.com/sahil-ramagiri>
 *
 *  Licensed under the MIT License.
 */

#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include <memory>
#include <string>
#include <vector>
#include "lodepng.h"

struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t alpha;
};

class FrameBuffer
{
public:
    
    FrameBuffer(size_t width, size_t height) : width(width), height(height),
        buffer(new color[width * height]) {}

    // ~FrameBuffer() = default;

    void set_pixel(size_t row, size_t col, uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255) {
        buffer[row * width + col] = {r,g,b,alpha};
    }

    color get_pixel(size_t row, size_t col) {
        return buffer[row * width + col];
    }

    void dump_to_file(std::string file_name){
        std::vector<unsigned char> image(width*height*4,0);
        // #pragma omp parallel for
        for (int idx=0;idx < width*height;idx++){
            image[4*idx + 0] = buffer[idx].r;
            image[4*idx + 1] = buffer[idx].g;
            image[4*idx + 2] = buffer[idx].b;
            image[4*idx + 3] = buffer[idx].alpha;
        }
        unsigned error = lodepng::encode(file_name, image, width, height);
        if(error) spdlog::error("encoder error {}: {}",error, lodepng_error_text(error));
        else spdlog::info("image written to {}",file_name);
    }

private:
    std::unique_ptr<color[]> buffer;
    size_t width;
    size_t height;
};

int main()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::stopwatch sw;

    const size_t image_width = 480;
    const size_t image_height = 320;

    FrameBuffer fb{image_width, image_height};

    // Render
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            uint8_t ir = static_cast<uint8_t>(255.999 * r);
            uint8_t ig = static_cast<uint8_t>(255.999 * g);
            uint8_t ib = static_cast<uint8_t>(255.999 * b);

            fb.set_pixel(j, i, ir, ig, ib);
        }
    }
    fb.dump_to_file("test.png");
    spdlog::debug("That took {:.3}s", sw);
    return 0;
}