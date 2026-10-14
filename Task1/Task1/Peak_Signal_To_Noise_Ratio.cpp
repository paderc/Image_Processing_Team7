#include "Peak_Signal_To_Noise_Ratio.h"

void Peak_Signal_To_Noise_Ratio::measure_inherited() {

	using pixel_type = decltype(image1)::value_type;

	const unsigned color_spectrum = image1.spectrum();

	double max = (1 << (sizeof(pixel_type) * 8)) - 1;
	
	double img1_sum = 0;
	double img2_sum = 0;
	cimg_forXYC(image1, x, y, c) {
		img1_sum += image1(x, y, c);
		img2_sum += image2(x, y, c);
	}
	double diff = img1_sum - img2_sum;
	error = 10 * log10((max * max) / (diff * diff));
};