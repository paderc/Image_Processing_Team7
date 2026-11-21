#include "Enlargement_Modifier.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>
void Enlargement_Modifier::modify_nearest_neighbour() {
	const double scale = factor;

	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();

	const double scaled_w = w * scale;
	const double scaled_h = h * scale;
	const double max_dimension = std::numeric_limits<int>::max();

	if (scaled_w > max_dimension || scaled_h > max_dimension)
		throw std::length_error("Requested image is too large.");

	const int new_w = static_cast<int>(scaled_w);
	const int new_h = static_cast<int>(scaled_h);

	CImg<unsigned char> output(new_w, new_h, 1, channels);

	std::vector<int> source_x(new_w);

	for (int x = 0; x < new_w; ++x) {
		source_x[x] = static_cast<int>(
			(std::uint64_t(x) * w) / new_w);
	}

	const std::size_t source_plane_size = std::size_t(w) * h;
	const std::size_t output_plane_size = std::size_t(new_w) * new_h;
	for (int c = 0; c < channels; ++c) {
		const auto* source_plane =
			image.data() + c * source_plane_size;

		auto* output_plane =
			output.data() + c * output_plane_size;

		for (int y = 0; y < new_h; ++y) {
			const int source_y = static_cast<int>(
				(std::uint64_t(y) * h) / new_h);

			const auto* source_row =
				source_plane + std::size_t(source_y) * w;

			auto* output_row =
				output_plane + std::size_t(y) * new_w;

			for (int x = 0; x < new_w; ++x) {
				output_row[x] = source_row[source_x[x]];
			}
		}
	}

	image = std::move(output);
}
void Enlargement_Modifier::modify_bilinear() {
	const int w = image.width();
	const int h = image.height();
	const int channels = image.spectrum();

	const int new_w = w * factor;
	const int new_h = h * factor;

	CImg<unsigned char> output(new_w, new_h, 1, channels);

	for (int j = 0; j < new_h; j++) {
		const double y = j / factor;
		for (int i = 0; i < new_w; i++) {
			const double x = i / factor;

			const int x_floor = int(x);
			const int x_ceil = std::ceil(x);
			const int y_floor = int(y);
			const int y_ceil = std::ceil(y);

			double value = 0;
			for (int c = 0; c < channels; c++) {
				if (x_ceil == x_floor && y_ceil == y_floor) {
					value = image(x_floor, y_floor, 0, c);
				}
				else if (x_ceil == x_floor) {
					unsigned char floor_val = image(x_floor, y_floor, 0, c);
					unsigned char ceil_val = image(x_floor, y_ceil, 0, c);

					value = ceil_val * (y - y_floor) + floor_val * (y_ceil - y);
				}
				else if (y_ceil == y_floor) {
					unsigned char floor_val = image(x_floor, y_floor, 0, c);
					unsigned char ceil_val = image(x_ceil, y_floor, 0, c);

					value = ceil_val * (x - x_floor) + floor_val * (x_ceil - x);
				}
				else {
					unsigned char v1 = image(x_floor, y_floor, 0, c);
					unsigned char v2 = image(x_ceil, y_floor, 0, c);

					unsigned char v3 = image(x_floor, y_ceil, 0, c);
					unsigned char v4 = image(x_ceil, y_ceil, 0, c);

					const int q1 = v1 * (x_ceil - x) + v2 * (x - x_floor);
					const int q2 = v3 * (x_ceil - x) + v4 * (x - x_floor);
					value = q1 * (y_ceil - y) + q2 * (y - y_floor);
				}
				value += 0.5;
				output(i, j, 0, c) = unsigned char(value > 255 ? 255 : (value < 0 ? 0 : value));
			}
		}
	}
	image = std::move(output);
}

void Enlargement_Modifier::modify_inherited() {
	if (factor == 1.0)
		return;
	if (lerp) {
		modify_bilinear();
	}
	else {
		modify_nearest_neighbour();
	}

}