#include "Median_Modifier.h"
#include <vector>
#include <algorithm>
using namespace std;

void Median_Modifier::modify_inherited() {
	using pixel_type = decltype(image)::value_type;

	const unsigned spectrum = image.spectrum();
	CImg<pixel_type> new_image(width, height, 1, spectrum);

	const int x_lo = -(m - 1) / 2, x_hi = m / 2;
	const int y_lo = -(n - 1) / 2, y_hi = n / 2;

	vector<pixel_type> values;
	values.reserve(m * n);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (unsigned c = 0; c < spectrum; c++) {
				values.clear();

				for (int i = x_lo; i <= x_hi; i++) {
					if (x + i < 0 || x + i >= width) continue;

					for (int j = y_lo; j <= y_hi; j++) {
						if (y + j < 0 || y + j >= height) continue;
						values.push_back(image(x + i, y + j, 0, c));
					}
				}
				const auto mid = values.begin() + values.size() / 2;
				nth_element(values.begin(), mid, values.end());
				new_image(x, y, 0, c) = *mid;
			}
		}
	}
	image = move(new_image);
}