#include "Variation_Coefficient_I.h"
#include "../Histograms/Histogram_Data.h"

void Variation_Coefficient_I::measure_inherited() {
	Intensity_Data data(image);
	score = sqrt(variance(data)) / mean(data);
}