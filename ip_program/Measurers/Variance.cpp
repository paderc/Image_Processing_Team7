#include "Variance.h"
#include "../Histograms/Histogram_Data.h"

void Variance::measure_inherited() {
	score = variance();
}