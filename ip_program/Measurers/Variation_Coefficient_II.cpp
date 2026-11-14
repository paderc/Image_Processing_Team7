#include "Variation_Coefficient_II.h"
#include "../Histograms/Histogram_Data.h"

void Variation_Coefficient_II::measure_inherited() {
	Intensity_Data data(image);
	const double N = static_cast<double>(image.width()) * static_cast<double>(image.height());
	if (N <= 0.0) {
		score = 0.0;
		return;
	}

	double sum_sq = 0.0;
	for (unsigned int h : data.occurences) {
		double dh = static_cast<double>(h);
		sum_sq += dh * dh;
	}
	score = sum_sq / (N * N);
}
