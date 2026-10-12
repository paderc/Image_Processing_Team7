#include "Brightness_Modifier.h"
#include <array>
#include <algorithm>
#include <cstddef>

using namespace std;

void Brightness_Modifier::modify_inherited() {
    using pixel_type = decltype(image)::value_type;

    constexpr int color_range = 1 << (sizeof(pixel_type) * 8);
    constexpr int allowed_values = color_range - 1;

    pixel_type lut[color_range];
    for (unsigned i = 0; i < allowed_values; i++) {
        int v = i + brightness;
        lut[i] = clamp(v, 0, allowed_values);
    }

    cimg_for(image, ptr, pixel_type) {
        *ptr = lut[*ptr];
    }
}