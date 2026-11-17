#include "Flattening_Coefficient.h"
#include "../Histograms/Histogram_Data.h"

void Flattening_Coefficient::measure_inherited() {
	Intensity_Data data(image);
	const double m = this->mean(data);
	const double var = this->variance(data);
	const double N = static_cast<double>(image.width()) * static_cast<double>(image.height());

	if (var <= 1e-12 || N <= 0.0) {
		score = 0.0;
		return;
	}

	double sum4 = 0.0;
	for (int i = 0; i < static_cast<int>(data.occurences.size()); ++i) {
		double diff = static_cast<double>(i) - m;
		double diff2 = diff * diff;
		sum4 += diff2 * diff2 * data.occurences.at(i);
	}
	score = (sum4 / (N * var * var)) - 3.0;
}
