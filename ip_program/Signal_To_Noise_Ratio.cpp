#include "Signal_To_Noise_Ratio.h"
#include <cmath>
#include <limits>

void Signal_To_Noise_Ratio::measure_inherited() {
    const auto* a = image1.data();
    const auto* b = image2.data();
    const auto count = image1.size();

    double signal = 0.0;
    double noise = 0.0;

    for (decltype(image1.size()) i = 0; i < count; ++i) {
        const int difference = int(a[i]) - int(b[i]);

        signal += double(a[i]) * a[i];
        noise += double(difference) * difference;
    }

    const double infinity = std::numeric_limits<double>::infinity();

    error = noise == 0.0 ? infinity : signal == 0.0 ? -infinity : 10.0 * std::log10(signal / noise);
}