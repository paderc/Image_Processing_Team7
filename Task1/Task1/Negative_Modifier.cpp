#include "Negative_Modifier.h"
#include <algorithm>
using namespace cimg_library;

void Negative_Modifier::modify_inherited() {
	using pixel_type = decltype(image)::value_type;
	constexpr int color_range = 1 << (sizeof(pixel_type) * 8);
	constexpr int allowed_values = color_range - 1;

	pixel_type lut[color_range];
	for (int i = 0; i < color_range ; i++) {
		int val = 255 - i;
		lut[i] = clamp(val, 0, allowed_values);
	}

	cimg_for(image, ptr, pixel_type) {
		*ptr = lut[*ptr];
	}
}