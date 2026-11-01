#include "Rotation_Modifier.h"
#include <cstddef>
#include <stdexcept>

void Rotation_Modifier::modify_inherited() {
    const std::size_t w = image.width();
    const std::size_t h = image.height();
    const std::size_t plane_size = w * h;

    auto swap_values = [](unsigned char& a, unsigned char& b) {
        const unsigned char temp = a;
        a = b;
        b = temp;
        };

    for (unsigned c = 0; c < image.spectrum(); ++c) {
        auto* plane = image.data() + c * plane_size;

        if (direction == "--hflip") {
            for (std::size_t y = 0; y < h; ++y) {
                auto* row = plane + y * w;

                for (std::size_t x = 0; x < w / 2; ++x)
                    swap_values(row[x], row[w - 1 - x]);
            }
        }
        else if (direction == "--vflip") {
            for (std::size_t y = 0; y < h / 2; ++y) {
                auto* top = plane + y * w;
                auto* bottom = plane + (h - 1 - y) * w;

                for (std::size_t x = 0; x < w; ++x)
                    swap_values(top[x], bottom[x]);
            }
        }
        else if (direction == "--dflip") {
            for (std::size_t i = 0; i < plane_size / 2; ++i)
                swap_values(plane[i], plane[plane_size - 1 - i]);
        }
    }
}