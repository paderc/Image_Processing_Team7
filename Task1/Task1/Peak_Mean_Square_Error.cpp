#include "Peak_Mean_Square_Error.h"
#include <limits>

void Peak_Mean_Square_Error::measure_inherited() {
	const double noise = squared_error_sum();
	const double peak = reference_peak();

	error = peak == 0.0 ? (noise == 0.0 ? 0.0 : std::numeric_limits<double>::infinity()) : noise / (double(image1.size()) * peak * peak);
};
string Peak_Mean_Square_Error::describe() {
	return string("PMSE between ").append(filename1).append(" and ").append(filename2).append(" is ").append(to_string(error));
};