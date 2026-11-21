#include "PowerTwoThird.h"
#include "../Histograms/Histogram_Data.h"
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <stdexcept>
#include <string_view>

namespace {
int parseBrightnessBound(std::string_view argument) {
	int value = 0;
	const char* end = argument.data() + argument.size();
	const auto parsed = std::from_chars(argument.data(), end, value);
	if (parsed.ec != std::errc{} || parsed.ptr != end || value < 0 || value > 255) {
		throw std::invalid_argument("H4 brightness bounds must be integers from 0 to 255.");
	}
	return value;
}
}

PowerTwoThird::PowerTwoThird(char* argv[])
	: Modifier(argv), g_min(parseBrightnessBound(argv[3])), g_max(parseBrightnessBound(argv[4])) {
	if (g_min > g_max) {
		throw std::invalid_argument("H4 requires g_min to be less than or equal to g_max.");
	}
}

void PowerTwoThird::modify_inherited() {
	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();
	const double N = static_cast<double>(w) * static_cast<double>(h);
	if (N <= 0.0) return;

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
