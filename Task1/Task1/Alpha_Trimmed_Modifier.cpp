#include "Alpha_Trimmed_Modifier.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

void Alpha_Trimmed_Modifier::modify_inherited() {
    using pixel_type = decltype(image)::value_type;

    const int w = image.width();
    const int h = image.height();

    CImg<pixel_type> output(w, h, 1, image.spectrum());

    const int x_lo = -(s - 1) / 2, x_hi = s / 2;
    const int y_lo = -(t - 1) / 2, y_hi = t / 2;

    std::vector<pixel_type> values;
    values.reserve(s * t);

    cimg_forC(image, c) {
        cimg_forXY(image, x, y) {
            values.clear();

            for (int ny = std::max(0, y + y_lo);
                ny <= std::min(h - 1, y + y_hi); ++ny) {
                for (int nx = std::max(0, x + x_lo);
                    nx <= std::min(w - 1, x + x_hi); ++nx) {
                    values.push_back(image(nx, ny, 0, c));
                }
            }

            const std::size_t trim = std::min<std::size_t>(
                d / 2, (values.size() - 1) / 2);

            auto first = values.begin() + trim;
            auto last = values.end() - trim;

            if (trim != 0) {
                std::nth_element(values.begin(), first, values.end());
                std::nth_element(first, last, values.end());
            }

            const int sum = std::accumulate(first, last, 0);
            const int count = static_cast<int>(last - first);

            output(x, y, 0, c) = static_cast<pixel_type>(
                (sum + count / 2) / count);
        }
    }

    image = std::move(output);
}