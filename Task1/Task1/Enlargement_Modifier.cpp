#include "Enlargement_Modifier.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

void Enlargement_Modifier::modify_inherited() {
    const double scale = factor;

    if (scale == 1.0)
        return;

    const int w = image.width();
    const int h = image.height();
    const int channels = image.spectrum();

    const double scaled_w = w * scale;
    const double scaled_h = h * scale;
    const double max_dimension = std::numeric_limits<int>::max();

    if (scaled_w > max_dimension || scaled_h > max_dimension)
        throw std::length_error("Requested image is too large.");

    const int new_w = static_cast<int>(scaled_w);
    const int new_h = static_cast<int>(scaled_h);

    CImg<unsigned char> output(new_w, new_h, 1, channels);

    std::vector<int> source_x(new_w);

    for (int x = 0; x < new_w; ++x) {
        source_x[x] = static_cast<int>(
            (std::uint64_t(x) * w) / new_w);
    }

    const std::size_t source_plane_size = std::size_t(w) * h;
    const std::size_t output_plane_size = std::size_t(new_w) * new_h;

    for (int c = 0; c < channels; ++c) {
        const auto* source_plane =
            image.data() + c * source_plane_size;

        auto* output_plane =
            output.data() + c * output_plane_size;

        for (int y = 0; y < new_h; ++y) {
            const int source_y = static_cast<int>(
                (std::uint64_t(y) * h) / new_h);

            const auto* source_row =
                source_plane + std::size_t(source_y) * w;

            auto* output_row =
                output_plane + std::size_t(y) * new_w;

            for (int x = 0; x < new_w; ++x)
                output_row[x] = source_row[source_x[x]];
        }
    }

    image = std::move(output);
}