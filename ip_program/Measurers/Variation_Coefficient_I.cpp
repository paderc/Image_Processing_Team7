#include "Variation_Coefficient_I.h"
#include "../Histograms/Histogram_Data.h"
#include <cmath>

void Variation_Coefficient_I::measure_inherited() {
	Intensity_Data data(image);
	double m = mean(data);
	if (std::abs(m) <= 1e-12) {
		score = 0.0;
		return;
	}
	score = std::sqrt(variance(data)) / m;
}
