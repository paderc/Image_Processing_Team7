#include "Variation_Coefficient_I.h"
#include "../Histograms/Histogram_Data.h"

void Variation_Coefficient_I::measure_inherited() {
	score = std_dev / mean();
}