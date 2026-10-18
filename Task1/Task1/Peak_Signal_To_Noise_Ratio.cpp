#include "Peak_Signal_To_Noise_Ratio.h"
#include <cmath>
#include <limits>

void Peak_Signal_To_Noise_Ratio::measure_inherited() {
    const double noise = squared_error_sum();
    const double peak = reference_peak();
    const double infinity = std::numeric_limits<double>::infinity();

    error = noise == 0.0 ? infinity : peak == 0.0 ? -infinity : 10.0 * std::log10(double(image1.size()) * peak * peak / noise);
};