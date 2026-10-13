#include <vector>

#include "Peak_Mean_Square_Error.h"
void Peak_Mean_Square_Error::measure_inherited() {
	using pixel_type = decltype(image1)::value_type;
	
	const unsigned color_spectrum = image1.spectrum();

	unsigned max = 0;
	cimg_for(image1, ptr, pixel_type) {
		unsigned v = *ptr;
		if (v > max) max = v;
	}
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			for (unsigned c = 0; c < color_spectrum; c++) {
				double d = double(image1(x, y, c)) - double(image2(x, y, c));
				error += d * d;
			}
		}
	}
	error /= double(height * width * max * max);
};
string Peak_Mean_Square_Error::describe() {
	return string("PMSE between ").append(filename1).append(" and ").append(filename2).append(" is ").append(to_string(error));
};