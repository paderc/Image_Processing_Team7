#include "Extraction_Details_I.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

void Extraction_Details_I::modify_inherited() {
	if (mode == "opt") {
		if (direction == "N" || direction == "n") {
			applyOptimizedNorth();
			return;
		}
		std::cerr << "Warning: Optimized mode is specialized for mask N; falling back to universal convolution.\n";
	}
	else if (mode != "universal") {
		throw std::invalid_argument("Choose universal or opt for the S3 filter mode.");
	}

	CImg<double> mask;
	if (direction == "N" || direction == "n") {
		mask = CImg<double>::matrix( 1,  1,  1,
		                             1, -2,  1,
		                            -1, -1, -1);
	}
	else if (direction == "NE" || direction == "ne") {
		mask = CImg<double>::matrix( 1,  1,  1,
		                            -1, -2,  1,
		                            -1, -1,  1);
	}
	else if (direction == "E" || direction == "e") {
		mask = CImg<double>::matrix(-1,  1,  1,
		                            -1, -2,  1,
		                            -1,  1,  1);
	}
	else if (direction == "SE" || direction == "se") {
		mask = CImg<double>::matrix(-1, -1,  1,
		                            -1, -2,  1,
		                             1,  1,  1);
	}
	else {
		throw std::invalid_argument("Choose N, NE, E, or SE for the S3 filter direction.");
	}

	applyUniversal(image, mask);
}

void Extraction_Details_I::applyUniversal(CImg<unsigned char>& image, const CImg<double>& mask) {
	const int mask_width = mask.width();
	const int mask_height = mask.height();
	if (mask_width % 2 == 0 || mask_height % 2 == 0 || mask.depth() != 1 || mask.spectrum() != 1) {
		throw std::invalid_argument("The filter mask must be a single-channel 2D matrix with odd dimensions.");
	}
	double total_weight = 0;
	for (const double weight : mask) {
		total_weight += std::abs(weight);
	}
	if (!(total_weight <= std::numeric_limits<double>::max() / 256.0)) {
		throw std::invalid_argument("Filter mask coefficients must be finite and within the calculation range.");
	}

	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();
	if (w < mask_width || h < mask_height) return;

	const int radius_x = mask_width / 2;
	const int radius_y = mask_height / 2;
	CImg<unsigned char> result(image);

	for (int c = 0; c < channels; ++c) {
		for (int y = radius_y; y < h - radius_y; ++y) {
			for (int x = radius_x; x < w - radius_x; ++x) {
				double sum = 0;
				const double* weight = mask.data();
				for (int dy = -radius_y; dy <= radius_y; ++dy) {
					const unsigned char* row = image.data(x - radius_x, y + dy, 0, c);
					for (int dx = 0; dx < mask_width; ++dx) {
						sum += *weight++ * row[dx];
					}
				}
				result(x, y, 0, c) = static_cast<unsigned char>(std::clamp(sum, 0.0, 255.0) + 0.5);
			}
		}
	}
	image = std::move(result);
}

// The north mask uses three top-minus-bottom differences and the middle row.
// Reuse two differences across adjacent outputs and keep two original rows.
void Extraction_Details_I::applyOptimizedNorth() {
	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();
	if (w < 3 || h < 3) return;

	std::vector<unsigned char> row_prev(w);
	std::vector<unsigned char> row_curr(w);

	for (int c = 0; c < channels; ++c) {
		unsigned char* plane = image.data(0, 0, 0, c);
		std::memcpy(row_prev.data(), plane, w);
		std::memcpy(row_curr.data(), plane + w, w);

		for (int y = 1; y < h - 1; ++y) {
			const unsigned char* r_top = row_prev.data();
			const unsigned char* r_mid = row_curr.data();
			const unsigned char* r_bot = plane + static_cast<size_t>(y + 1) * w;
			unsigned char* r_out = plane + static_cast<size_t>(y) * w;

			int diff_left = r_top[0] - r_bot[0];
			int diff_mid = r_top[1] - r_bot[1];

			for (int x = 1; x < w - 1; ++x) {
				const int diff_right = r_top[x + 1] - r_bot[x + 1];
				const int center = r_mid[x];
				const int val = diff_left + diff_mid + diff_right
					+ r_mid[x - 1] + r_mid[x + 1] - (center << 1);
				r_out[x] = static_cast<unsigned char>(std::clamp(val, 0, 255));

				diff_left = diff_mid;
				diff_mid = diff_right;
			}

			if (y + 1 < h - 1) {
				std::swap(row_prev, row_curr);
				std::memcpy(row_curr.data(), r_bot, w);
			}
		}
	}
}
