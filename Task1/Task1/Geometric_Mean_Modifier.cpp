#include "Geometric_Mean_Modifier.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void Geometric_Mean_Modifier::modify_inherited() {
	using pixel_type = decltype(image)::value_type;
	const double possible_values = (1 << (sizeof(pixel_type) * 8)) - 1;

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
				double final = 1;
				for (auto v : values) {
					final *= v;
				}
				final = pow(final, 1 / double(m * n));
				new_image(x, y, 0, c) = static_cast<pixel_type>(clamp(final, 0.0, possible_values));
			}
		}
	}
	image = move(new_image);
}

string Geometric_Mean_Modifier::make_name(string_view base_name, string_view extension) {
	return string(base_name).append("_gmean_").append(to_string(m)).append("_").append(to_string(n)).append(extension);
}