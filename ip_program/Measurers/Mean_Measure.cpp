#include "Mean_Measure.h"
#include "../Histograms/Histogram_Data.h"

void Mean_Measure::measure_inherited() {
	Intensity_Data data(image);
	score = mean(data);
}