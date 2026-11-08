#include "Histogram_Data.h"
#include <math.h>

unsigned char BLACK[3] = { 0, 0, 0 };
unsigned char WHITE[3] = { 255, 255, 255 };
unsigned char BLUE[3] = {0, 0, 255};
unsigned char GREEN[3] = { 0, 255, 0 };
unsigned char RED[3] = { 255, 0, 0 };

constexpr int DIVIDER_COUNT = 10;
constexpr int ARROW_OFFSET = 30;

void Intensity_Data::fill_data() {
	//reset to zero
	for (auto& val : occurences) {
		val = 0;
	}

	for (int y = 0; y < image.height(); y++) {
		for (int x = 0; x < image.width(); x++) {
			float sum = 0;
			for (int k = 0; k < image.spectrum(); k++) {
				sum += image.atXYZC(x, y, 0, k);
			}
			unsigned char intensity = static_cast<unsigned char>(sum / image.spectrum());
			occurences.at(intensity)++;
		}
	}
}

CImg<unsigned char> Intensity_Data::makeGraph(int width, int height, bool darkMode) {
	const unsigned char* THEME_COLOR = darkMode ? WHITE : BLACK;
	const unsigned char* DATA_COLOR = darkMode ? BLACK : WHITE;

	CImg<unsigned char> chart(width, height, 1, 3);
	chart.fill(THEME_COLOR[0], THEME_COLOR[1], THEME_COLOR[2]);

	const int top = height / 10;
	const int left = width / 10;
	const int right = width - left;
	const int bottom = height - top;

	const int plot_x = right - left;
	const int plot_y = bottom - top - ARROW_OFFSET;

	chart.draw_arrow<unsigned char>(left, bottom, left, top, DATA_COLOR);
	chart.draw_line<unsigned char>(left, bottom, right, bottom, DATA_COLOR);

	float size = occurences.size();
	float values_per_pixel = plot_y / size;
	if (values_per_pixel < 1) values_per_pixel = 1;

	float bar_length = plot_x / size;

	for (int i = 0; i < size; i++) {
		const int start_x = left + i * bar_length;
		chart.draw_rectangle<unsigned char>(start_x, bottom - (values_per_pixel * occurences.at(i)), start_x + bar_length, bottom, DATA_COLOR, 1.0);
	}
	chart.save("histogram.bmp");

	return chart;
}

void Divided_Data::fill_data() {
	//reset to zero
	for (auto& val : spectrum_occurences) {
		for (auto& inner_val : val) {
			inner_val = 0;
		}
	}
	for (int y = 0; y < image.height(); y++) {
		for (int x = 0; x < image.width(); x++) {
			for (int k = 0; k < image.spectrum(); k++) {
				unsigned char value = image.atXYZC(x, y, 0, k);
				spectrum_occurences.at(value).at(k)++;
			}
		}
	}
}

CImg<unsigned char> Divided_Data::makeGraph(int width, int height, bool darkMode) {
	
	const unsigned char* THEME_COLOR = darkMode ? WHITE : BLACK;
	const unsigned char* DATA_COLOR = darkMode ? BLACK : WHITE;
	const unsigned char* COLORS[3] = { RED, GREEN, BLUE };

	CImg<unsigned char> chart(width, height, 1, 3);
	chart.fill(THEME_COLOR[0], THEME_COLOR[1], THEME_COLOR[2]);
	const int top = height / 10;
	const int left = width / 10 + 1;
	const int right = width - left;
	const int bottom = height - top - ARROW_OFFSET;

	const int plot_x = right - left;
	const int plot_y = bottom - top - ARROW_OFFSET;

	chart.draw_arrow<unsigned char>(left - 1, bottom + 1, left - 1, top, DATA_COLOR);
	chart.draw_line<unsigned char>(left - 1, bottom + 1, right, bottom + 1, DATA_COLOR);
	const int size = static_cast<int>(spectrum_occurences.size());
	if (size <= 0) return chart;

	unsigned int max_count = 1;
	for (const auto& v : spectrum_occurences)
		for (auto c : v)
			if (c > max_count) max_count = c;

	const float y_scale = static_cast<float>(plot_y) / max_count;

	for (int i = 0; i < size; ++i) {
		const int group_x0 = left + (i * plot_x) / size;
		const int group_x1 = left + ((i + 1) * plot_x) / size;
		const int group_w = group_x1 - group_x0;
		if (group_w <= 0) continue;

		const int channels = static_cast<int>(spectrum_occurences[i].size());
		for (int k = 0; k < channels && k < 3; ++k) {
			const int bar_x0 = group_x0 + (k * group_w) / channels;
			const int bar_x1 = group_x0 + ((k + 1) * group_w) / channels;
			if (bar_x1 <= bar_x0) continue;

			const unsigned int value = spectrum_occurences[i][k];
			if (value == 0) continue;

			int h = static_cast<int>(value * y_scale + 0.5f);
			if (h < 1) h = 1;
			if (h > plot_y) h = plot_y;

			const int y1 = bottom;
			const int y0 = bottom - h + 1;

			chart.draw_rectangle<unsigned char>(
				bar_x0, y0,
				bar_x1 - 1, y1,
				COLORS[k], 1.0f
			);
		}
	}
	chart.save("histogram.bmp");

	return chart;
}