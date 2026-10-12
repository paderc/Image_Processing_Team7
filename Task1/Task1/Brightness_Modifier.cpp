#include "Brightness_Modifier.h"
#include <array>
#include <algorithm>
#include <cstddef>

void Brightness_Modifier::modify_inherited() {
    using pixel_type = decltype(image)::value_type;

    constexpr std::size_t range = std::size_t{ 1 } << (sizeof(pixel_type) * 8);
    constexpr int max_val = static_cast<int>(range) - 1;

    std::array<pixel_type, range> lut{};
    for (std::size_t i = 0; i < range; i++) {
        int v = static_cast<int>(i) + brightness;
        v = std::clamp(v, 0, max_val);
        lut[i] = static_cast<pixel_type>(v);
    }

    cimg_for(image, ptr, pixel_type) {
        *ptr = lut[*ptr];
    }
}