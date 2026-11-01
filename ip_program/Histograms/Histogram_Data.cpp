#include "Histogram_Data.h"
#include <math.h>

unsigned char BLACK[3] = { 0, 0, 0 };
unsigned char WHITE[3] = { 255, 255, 255 };
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
	fill_data();
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