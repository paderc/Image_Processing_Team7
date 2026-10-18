#include "Geometric_Mean_Modifier.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <utility>

void Geometric_Mean_Modifier::modify_inherited() {
    static const auto log_lut = [] {
        std::array<double, 256> table{};

        for (int i = 1; i < 256; ++i)
            table[i] = std::log(double(i));

        return table;
        }();

    const int w = image.width();
    const int h = image.height();

    CImg<unsigned char> output(w, h, 1, image.spectrum());

    const int x_lo = -(m - 1) / 2, x_hi = m / 2;
    const int y_lo = -(n - 1) / 2, y_hi = n / 2;

    cimg_forC(image, c) {
        cimg_forXY(image, x, y) {
            double sum_log = 0.0;
            int count = 0;
            bool has_zero = false;

            for (int ny = std::max(0, y + y_lo);
                ny <= std::min(h - 1, y + y_hi); ++ny) {
                for (int nx = std::max(0, x + x_lo);
                    nx <= std::min(w - 1, x + x_hi); ++nx) {
                    const auto value = image(nx, ny, 0, c);

                    has_zero |= value == 0;
                    sum_log += log_lut[value];
                    ++count;
                }
            }

            const double mean =
                has_zero ? 0.0 : std::exp(sum_log / count);

            output(x, y, 0, c) = static_cast<unsigned char>(
                std::clamp(std::lround(mean), 0L, 255L));
        }
    }

    image = std::move(output);
}

string Geometric_Mean_Modifier::make_name(string_view base_name, string_view extension) {
	return string(base_name).append("_gmean_").append(to_string(m)).append("_").append(to_string(n)).append(extension);
}