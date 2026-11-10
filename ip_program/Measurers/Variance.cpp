#include "Variance.h"
#include "../Histograms/Histogram_Data.h"

void Variance::measure_inherited() {
	Intensity_Data data(image);
	score = variance(data);
}