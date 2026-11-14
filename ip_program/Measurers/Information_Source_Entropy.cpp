#include "Information_Source_Entropy.h"
#include "../Histograms/Histogram_Data.h"
#include <cmath>

void Information_Source_Entropy::measure_inherited() {
	Intensity_Data data(image);
	const double N = static_cast<double>(image.width()) * static_cast<double>(image.height());
	if (N <= 0.0) {
		score = 0.0;
		return;
	}

	double entropy = 0.0;
	for (unsigned int h : data.occurences) {
		if (h > 0) {
			double p = static_cast<double>(h) / N;
			entropy -= p * std::log2(p);
		}
	}
	score = entropy;
}
