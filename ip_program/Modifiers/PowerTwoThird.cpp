#include "PowerTwoThird.h"
#include "../Histograms/Histogram_Data.h"
#include <algorithm>
#include <array>
#include <cmath>

void PowerTwoThird::modify_inherited() {
	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();
	const double N = static_cast<double>(w) * static_cast<double>(h);
	if (N <= 0.0) return;

	g_min = std::clamp(g_min, 0, 255);
	g_max = std::clamp(g_max, 0, 255);

	const double cbrt_min = std::cbrt(static_cast<double>(g_min));
	const double cbrt_range = std::cbrt(static_cast<double>(g_max)) - cbrt_min;

	Divided_Data hist_data(image);

	for (int c = 0; c < channels; ++c) {
		std::array<unsigned char, 256> lut{};
		unsigned long long cumulative = 0;

		for (int f = 0; f < 256; ++f) {
			cumulative += hist_data.spectrum_occurences[f][c];
			double cdf = static_cast<double>(cumulative) / N;
			double root_val = cbrt_min + cbrt_range * cdf;
			double g = root_val * root_val * root_val;
			lut[f] = static_cast<unsigned char>(std::clamp(static_cast<int>(std::round(g)), 0, 255));
		}

		cimg_forXY(image, x, y) {
			image(x, y, 0, c) = lut[image(x, y, 0, c)];
		}
	}
}
