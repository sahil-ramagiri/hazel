#pragma once

#include "types.h"
#include "lodepng.h"
#include "spdlog/spdlog.h"

#include "glm/glm.hpp"

class FrameBuffer
{
public:

    FrameBuffer(size_t width, size_t height) : m_width(width), m_height(height),
        buffer(new color[width * height]) {}

    // ~FrameBuffer() = default;
    size_t width(){
        return m_width;
    }
    size_t height(){
        return m_height;
    }

    void set_pixel(size_t row, size_t col, double r, double g, double b, double alpha = 1.0) {
        buffer[row * m_width + col] = { r,g,b,alpha };
    }
    void set_pixel(size_t row, size_t col, color& c) {
        buffer[row * m_width + col] = c;
    }

    color get_pixel(size_t row, size_t col) {
        return buffer[row * m_width + col];
    }

    void clamp() {
        for (int idx = 0;idx < m_width * m_height;idx++) {
            buffer[idx] = glm::clamp(buffer[idx], 0.0, 1.0);
        }
    }
    void no_alpha(){
        for (int idx = 0;idx < m_width * m_height;idx++) {
            buffer[idx].a = 1.0;
        }
    }

    void dump_to_file(std::string file_name) {
        clamp();
        no_alpha();
        std::vector<unsigned char> image(m_width * m_height * 4, 0);
        // #pragma omp parallel for
        for (int idx = 0;idx < m_width * m_height;idx++) {
            image[4 * idx + 0] = static_cast<uint8_t>(255.999 * buffer[idx].r);
            image[4 * idx + 1] = static_cast<uint8_t>(255.999 * buffer[idx].g);
            image[4 * idx + 2] = static_cast<uint8_t>(255.999 * buffer[idx].b);
            image[4 * idx + 3] = static_cast<uint8_t>(255.999 * buffer[idx].a);
        }
        unsigned int error = lodepng::encode(file_name, image, unsigned(m_width), unsigned(m_height));
        if (error) spdlog::error("encoder error {}: {}", error, lodepng_error_text(error));
        else spdlog::info("image written to {}", file_name);
    }

private:
    std::unique_ptr<color[]> buffer;
    size_t m_width;
    size_t m_height;
};