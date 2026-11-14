#include "Histogram_Data.h"
#include <algorithm>
#include <cmath>
#include <string>

unsigned char BLACK[3] = { 0, 0, 0 };
unsigned char WHITE[3] = { 255, 255, 255 };
unsigned char BLUE[3] = { 0, 0, 255 };
unsigned char GREEN[3] = { 0, 255, 0 };
unsigned char RED[3] = { 255, 0, 0 };

constexpr int ARROW_OFFSET = 30;

namespace {
void drawAxesAndLabels(
	CImg<unsigned char>& chart,
	int left, int right, int top, int bottom,
	int plot_x, int plot_y,
	unsigned int max_count,
	const unsigned char* data_color)
{
	chart.draw_line<unsigned char>(left, bottom, left, top, data_color);
	chart.draw_line<unsigned char>(left, bottom, right, bottom, data_color);

	const unsigned int font_h = 16;

	const int x_ticks[5] = { 0, 64, 128, 192, 255 };
	for (int bin : x_ticks) {
		int tx = left + (bin * plot_x) / 256;
		chart.draw_line<unsigned char>(tx, bottom, tx, bottom + 5, data_color);
		std::string lbl = std::to_string(bin);
		int text_w = static_cast<int>(lbl.size()) * 8;
		chart.draw_text(tx - text_w / 2, bottom + 9, lbl.c_str(), data_color, 0, 1.0f, font_h);
	}
	chart.draw_text(left + plot_x / 2 - 36, bottom + 30, "Intensity", data_color, 0, 1.0f, font_h);

	const unsigned int y_vals[3] = { 0u, max_count / 2u, max_count };
	const int y_pos[3] = { bottom, bottom - plot_y / 2, bottom - plot_y };
	for (int idx = 0; idx < 3; ++idx) {
		int ty = y_pos[idx];
		chart.draw_line<unsigned char>(left - 5, ty, left, ty, data_color);
		std::string lbl = std::to_string(y_vals[idx]);
		int text_w = static_cast<int>(lbl.size()) * 8;
		int lx = std::max(4, left - 9 - text_w);
		chart.draw_text(lx, ty - static_cast<int>(font_h / 2), lbl.c_str(), data_color, 0, 1.0f, font_h);
	}
	chart.draw_text(std::max(4, left - 24), top - 22, "Count", data_color, 0, 1.0f, font_h);
}
}

void Intensity_Data::fill_data() {
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
	if (width < 1024) width = 1024;
	if (height < 640) height = 640;

	const unsigned char* THEME_COLOR = darkMode ? WHITE : BLACK;
	const unsigned char* DATA_COLOR = darkMode ? BLACK : WHITE;

	CImg<unsigned char> chart(width, height, 1, 3);
	chart.fill(THEME_COLOR[0], THEME_COLOR[1], THEME_COLOR[2]);

	const int top = height / 10;
	const int left = width / 10;
	const int right = width - left / 2;
	const int bottom = height - top;

	const int plot_x = right - left;
	const int plot_y = bottom - top - ARROW_OFFSET;

	const int size = static_cast<int>(occurences.size());
	if (size <= 0) return chart;

	unsigned int max_count = 1;
	for (unsigned int c : occurences) {
		if (c > max_count) max_count = c;
	}

	drawAxesAndLabels(chart, left, right, top, bottom, plot_x, plot_y, max_count, DATA_COLOR);

	const float y_scale = static_cast<float>(plot_y) / max_count;
	const float bar_length = static_cast<float>(plot_x) / size;

	for (int i = 0; i < size; i++) {
		if (occurences[i] == 0) continue;
		const int start_x = static_cast<int>(left + i * bar_length);
		const int end_x = std::max(start_x + 1, static_cast<int>(left + (i + 1) * bar_length));
		int h = static_cast<int>(occurences[i] * y_scale + 0.5f);
		if (h < 1) h = 1;
		if (h > plot_y) h = plot_y;
		chart.draw_rectangle<unsigned char>(start_x, bottom - h, end_x - 1, bottom - 1, DATA_COLOR, 1.0f);
	}
	chart.save("histogram.bmp");

	return chart;
}

void Divided_Data::fill_data() {
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
	if (width < 1024) width = 1024;
	if (height < 640) height = 640;

	const unsigned char* THEME_COLOR = darkMode ? WHITE : BLACK;
	const unsigned char* DATA_COLOR = darkMode ? BLACK : WHITE;
	const unsigned char* COLORS[3] = { RED, GREEN, BLUE };

	CImg<unsigned char> chart(width, height, 1, 3);
	chart.fill(THEME_COLOR[0], THEME_COLOR[1], THEME_COLOR[2]);

	const int top = height / 10;
	const int left = width / 10;
	const int right = width - left / 2;
	const int bottom = height - top;

	const int plot_x = right - left;
	const int plot_y = bottom - top - ARROW_OFFSET;

	const int size = static_cast<int>(spectrum_occurences.size());
	if (size <= 0) return chart;

	unsigned int max_count = 1;
	for (const auto& v : spectrum_occurences)
		for (auto c : v)
			if (c > max_count) max_count = c;

	drawAxesAndLabels(chart, left, right, top, bottom, plot_x, plot_y, max_count, DATA_COLOR);

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

			const int y1 = bottom - 1;
			const int y0 = bottom - h;

			chart.draw_rectangle<unsigned char>(
				bar_x0, y0,
				bar_x1 - 1, y1,
				COLORS[k], 1.0f
			);
		}
	}

	if (!spectrum_occurences.empty() && spectrum_occurences[0].size() >= 3) {
		const char* names[3] = { "R", "G", "B" };
		for (int k = 0; k < 3; ++k) {
			int lx = right - 140 + k * 45;
			int ly = top - 18;
			chart.draw_rectangle<unsigned char>(lx, ly + 2, lx + 12, ly + 14, COLORS[k], 1.0f);
			chart.draw_text(lx + 16, ly, names[k], DATA_COLOR, 0, 1.0f, 16);
		}
	}

	chart.save("histogram.bmp");

	return chart;
}
