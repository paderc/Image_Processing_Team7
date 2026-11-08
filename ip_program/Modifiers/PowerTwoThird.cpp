#include "PowerTwoThird.h"
#include "../Histograms/Histogram_Data.h"

void PowerTwoThird::modify_inherited() {
	using pixel_type = decltype(image)::value_type;

	size_t range = std::numeric_limits<pixel_type>::max();

	// Implement the power two-thirds modification logic here
	Intensity_Data intensity_data(image);

	float g_min_to_onethird = pow(g_min, 1.0 / 3.0);
	float g_max_to_onethird = pow(g_max, 1.0 / 3.0);
	float one_over_N = 1.0f / (image.width() * image.height());

	vector<float> factor_lut(range + 1, -1.0f);

	cimg_forXY(image, x, y) {
		int sum = 0;
		int intensity = 0;
		for (int c = 0; c < image.spectrum(); c++) {
			intensity += image(x, y, 0, c);
		}
		intensity /= clamp(image.spectrum(), 0, 255);
		if (factor_lut[intensity] < 0) {
			for (int m = 0; m < intensity; m++) {
				sum += intensity_data.occurences[m];
			}
			float factor = pow((g_min_to_onethird + (g_max_to_onethird - g_min_to_onethird) * sum * one_over_N), 3.0f) / intensity;
			for (int c = 0; c < image.spectrum(); c++) {
				image(x, y, 0, c) = clamp(static_cast<int>(image(x, y, 0, c) * factor), 0, 255);
			}
		}
		else {
			for (int c = 0; c < image.spectrum(); c++) {
				image(x, y, 0, c) = clamp(static_cast<int>(image(x, y, 0, c) * factor_lut[intensity]), 0, 255);
			}
		}
	}
}