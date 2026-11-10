#include "Asymmetry_Coefficient.h"
#include "../Histograms/Histogram_Data.h"

void Asymmetry_Coefficient::measure_inherited() {
	Intensity_Data data(image);

	double mean = this->mean(data);
	double standard_deviation = sqrt(this->variance(data));
	double sum = 0;
	
	for (int i = 0; i < data.occurences.size(); i++) {
		sum += (pow(i - mean, 3) * data.occurences.at(i));
	}
	score = sum / (image.width() * image.height() * pow(standard_deviation, 3));
}