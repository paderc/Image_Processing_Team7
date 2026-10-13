#include "Signal_To_Noise_Ratio.h"
#include <math.h>

void Signal_To_Noise_Ratio::measure_inherited() {
	double img1_sum = 0;
	double img2_sum = 0;
	cimg_forXYC(image1, x, y, c) {
		img1_sum += image1(x, y, c);
		img2_sum += image2(x, y, c);
	}
	error = (img1_sum * img1_sum) / ((img1_sum - img2_sum) * (img1_sum - img2_sum));
}