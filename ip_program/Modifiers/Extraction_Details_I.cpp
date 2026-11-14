#include "Extraction_Details_I.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

void Extraction_Details_I::modify_inherited() {
	if (mode == "opt") {
		if (direction == "N" || direction == "n") {
			applyOptimizedNorth();
			return;
		}
		std::cerr << "Warning: Optimized mode is specialized for mask N; falling back to universal convolution.\n";
	}

	std::array<std::array<int, 3>, 3> mask{};
	if (direction == "N" || direction == "n") {
		mask = {{ { 1,  1, -1},
		          { 1, -2, -1},
		          { 1,  1, -1} }};
	}
	else if (direction == "NE" || direction == "ne") {
		mask = {{ { 1, -1, -1},
		          { 1, -2, -1},
		          { 1,  1,  1} }};
	}
	else if (direction == "E" || direction == "e") {
		mask = {{ {-1, -1, -1},
		          { 1, -2,  1},
		          { 1,  1,  1} }};
	}
	else if (direction == "SE" || direction == "se") {
		mask = {{ {-1, -1,  1},
		          {-1, -2,  1},
		          { 1,  1,  1} }};
	}
	else {
		std::cerr << "Unknown direction '" << direction << "'. Use N, NE, E, or SE.\n";
		return;
	}

	applyUniversal(mask);
}

// 1. Universal 3x3 spatial convolution (works for any 3x3 mask; allocates full output copy)
void Extraction_Details_I::applyUniversal(const std::array<std::array<int, 3>, 3>& mask) {
	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();

	CImg<unsigned char> result(image); // Preserves border pixels: g(p, q) = x(p, q)

	for (int c = 0; c < channels; ++c) {
		for (int y = 1; y < h - 1; ++y) {
			for (int x = 1; x < w - 1; ++x) {
				int acc = 0;
				for (int i = -1; i <= 1; ++i) {
					for (int j = -1; j <= 1; ++j) {
						acc += mask[i + 1][j + 1] * static_cast<int>(image(x + j, y + i, 0, c));
					}
				}
				result(x, y, 0, c) = static_cast<unsigned char>(std::clamp(acc, 0, 255));
			}
		}
	}
	image = std::move(result);
}

// 2. Optimized in-place convolution for S3 North mask:
//    [ 1,  1, -1 ]
//    [ 1, -2, -1 ]
//    [ 1,  1, -1 ]
//    - 0 multiplications (uses bit-shift << 1 for 2*center)
//    - 5 add/sub ops per pixel via sliding 3-pixel vertical column sums
//    - 2 * W bytes auxiliary memory (2-row ring buffer instead of W * H * C)
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
			const unsigned char* r_bot = plane + (y + 1) * w;
			unsigned char* r_out = plane + y * w;

			int col_left = r_top[0] + r_mid[0] + r_bot[0];
			int col_mid  = r_top[1] + r_mid[1] + r_bot[1];

			for (int x = 1; x < w - 1; ++x) {
				int col_right = r_top[x + 1] + r_mid[x + 1] + r_bot[x + 1]; // 2 additions
				int center = r_mid[x];

				int val = col_left + (col_mid - center) - (center << 1) - col_right; // 3 add/sub + 1 shift
				r_out[x] = static_cast<unsigned char>(val < 0 ? 0 : (val > 255 ? 255 : val));

				col_left = col_mid;
				col_mid = col_right;
			}

			if (y + 1 < h - 1) {
				std::swap(row_prev, row_curr);
				std::memcpy(row_curr.data(), r_bot, w);
			}
		}
	}
}
