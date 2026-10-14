#include "Maximum_Difference.h"

using namespace cimg_library;

void Maximum_Difference::measure_inherited() {
	int total_diff = 0;
	
	unsigned color_spectrum = image1.spectrum();

	cimg_forXY(image1, x, y) {
		int current_total = 0;
		for (int c = 0; c < color_spectrum; c++) {
			current_total += abs(image1(x, y, c) - image2(x, y, c));
		}
		if (current_total > total_diff) total_diff = current_total;
	}
	error = total_diff;
}