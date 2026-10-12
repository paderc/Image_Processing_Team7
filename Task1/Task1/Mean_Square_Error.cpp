#include "Mean_Square_Error.h"

void Mean_Square_Error::measure_inherited() {
	unsigned int color_spectrum = image1.spectrum();
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			for (unsigned c = 0; c < color_spectrum; c++) {
				double d = double(image1(x, y, c)) - double(image2(x, y, c));
				error += d * d;
			}
		}
	}
	error *= (1 / double(height * width));
}