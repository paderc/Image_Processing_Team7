#include "Contrast_Modifier.h"
#include <algorithm>

using namespace std;
using namespace cimg_library;

void Contrast_Modifier::modify_inherited() {
	using pixel_type = decltype(image)::value_type;
	constexpr int color_range = 1 << (sizeof(pixel_type) * 8);
	constexpr int allowed_values = color_range - 1;

	contrast = clamp(contrast, -100, 100);
	unsigned factor = (105 * (contrast + 100)) / (100 * (105 - contrast));

	pixel_type lut[color_range];
	for (int i = 0; i < allowed_values; i++) {
		int v = i * factor;
		lut[i] = clamp(v, 0, allowed_values);
	}

	cimg_for(image, ptr, pixel_type) {
		*ptr = lut[*ptr];
	}
}