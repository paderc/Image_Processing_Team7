#include "Shrinking_Modifier.h"
#include <algorithm>
using namespace std;

void Shrinking_Modifier::modify_inherited() {
	using pixel_type = decltype(image)::value_type;

	unsigned spectrum = image.spectrum();
	factor = clamp(factor, 0.0, 1.0);
	int des_width = factor * width;
	int des_height = factor * height;
	
	if (factor == 0.0) image = CImg<pixel_type>(1, 1, 1, spectrum, 0);
	else if (factor == 1.0) return;

	int smash = 1 / factor;
	int smash_squared = smash * smash;

	CImg<pixel_type> new_image(des_width, des_height, 1, spectrum);
	int sum = 0;
	for (int y = 0; y < des_height; y++) {
		for (int x = 0; x < des_width; x++) {
			for (int c = 0; c < spectrum; c++) {
				int pixel_no = 0;
				sum = 0;
				for (int i = 0; i < smash; i++) {
					for (int j = 0; j < smash; j++) {
						sum += image(x * smash + i, y * smash + j, c);
						pixel_no++;
					}
				}
				new_image(x, y, c) = static_cast<pixel_type>(sum / smash_squared);
			}
		}
	}
	image = move(new_image);
}