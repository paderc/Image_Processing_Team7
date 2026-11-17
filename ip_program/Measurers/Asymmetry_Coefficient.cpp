#include "Asymmetry_Coefficient.h"
#include "../Histograms/Histogram_Data.h"
#include <cmath>

void Asymmetry_Coefficient::measure_inherited() {
	Intensity_Data data(image);

	double m = this->mean(data);
	double standard_deviation = std::sqrt(this->variance(data));
	const double N = static_cast<double>(image.width()) * static_cast<double>(image.height());
	if (standard_deviation <= 1e-12 || N <= 0.0) {
		score = 0.0;
		return;
	}

	double sum = 0.0;
	for (int i = 0; i < static_cast<int>(data.occurences.size()); i++) {
		double diff = static_cast<double>(i) - m;
		sum += diff * diff * diff * data.occurences.at(i);
	}
	score = sum / (N * standard_deviation * standard_deviation * standard_deviation);
}
