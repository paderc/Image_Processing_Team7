#include "Noise_Maker.h"

void Noise_Maker::modify_inherited() {
	unsigned constexpr MAX_HARSHNESS = 10u;
	harshness = clamp(harshness, 0u, MAX_HARSHNESS);
	
	using pixel_type = decltype(image)::value_type;
	unsigned colors = image.spectrum();
	unsigned color_range = 1 << (sizeof(pixel_type) * 8);
	unsigned possible_values = color_range - 1;

	int pity = 0;
	cimg_for(image, ptr, pixel_type) {
		if (rand() % (MAX_HARSHNESS << 1) < harshness + pity) {
			for (unsigned c = 0; c < colors; c++) {
				pity = 0;
				*ptr = rand() % possible_values;

			}
		}
		else pity++;
	}
}