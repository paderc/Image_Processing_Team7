#include "Alpha_Trimmed_Modifier.h"
#include <vector>
#include <algorithm>
#include <numeric>

void Alpha_Trimmed_Modifier::modify_inherited() {
    s = std::clamp(int(s), 0, 13);
    t = std::clamp(int(t), 0, 13);

    using pixel_type = decltype(image)::value_type;
    using color_vector = std::vector<pixel_type>;

    const unsigned channels = image.spectrum();

    const int x_lo = -(s - 1) / 2, x_hi = s / 2;
    const int y_lo = -(t - 1) / 2, y_hi = t / 2;

    std::vector<pixel_type> channel_values;
    channel_values.reserve(s * t);

    cimg_forXY(image, x, y) {
        std::vector<color_vector> neighbourhood;
        neighbourhood.reserve(s * t);

        for (int j = y_lo; j <= y_hi; ++j) {
            const int ny = y + j;
            if (ny < 0 || ny >= height) continue;

            for (int i = x_lo; i <= x_hi; ++i) {
                const int nx = x + i;
                if (nx < 0 || nx >= width) continue;

                color_vector cv(channels);
                for (unsigned c = 0; c < channels; ++c)
                    cv[c] = image(nx, ny, c);

                neighbourhood.push_back(std::move(cv));
            }
        }

        const std::size_t n = neighbourhood.size();
        if (n == 0) continue;

        const std::size_t trim = (n / 2) / 2;
        if (2 * trim >= n) continue;

        for (unsigned c = 0; c < channels; ++c) {
            channel_values.clear();
            for (const auto& px : neighbourhood)
                channel_values.push_back(px[c]);

            std::sort(channel_values.begin(), channel_values.end());

            long long sum = 0;
            for (std::size_t k = trim; k < n - trim; ++k)
                sum += channel_values[k];

            const auto mean = static_cast<double>(sum) / double(n - 2 * trim);
            image(x, y, c) = static_cast<pixel_type>(mean + 0.5);
        }
    }
}