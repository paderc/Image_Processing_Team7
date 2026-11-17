#include "Roberts_II_Modifier.h"
#include <algorithm>
#include <cstdlib>

void Roberts_II_Modifier::modify_inherited() {
	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();

	CImg<unsigned char> result(image);

	for (int c = 0; c < channels; ++c) {
		for (int y = 0; y < h - 1; ++y) {
			for (int x = 0; x < w - 1; ++x) {
				int d1 = std::abs(static_cast<int>(image(x, y, 0, c)) - static_cast<int>(image(x + 1, y + 1, 0, c)));
				int d2 = std::abs(static_cast<int>(image(x, y + 1, 0, c)) - static_cast<int>(image(x + 1, y, 0, c)));
				int g = d1 + d2;
				result(x, y, 0, c) = static_cast<unsigned char>(g > 255 ? 255 : g);
			}
		}
	}
	image = std::move(result);
}
