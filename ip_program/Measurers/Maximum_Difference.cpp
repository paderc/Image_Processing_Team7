#include "Maximum_Difference.h"
#include <algorithm>
#include <cstdlib>

using namespace cimg_library;

void Maximum_Difference::measure_inherited() {
    const auto* a = image1.data();
    const auto* b = image2.data();
    const auto count = image1.size();

    int maximum = 0;

    for (decltype(image1.size()) i = 0; i < count; ++i)
    {
        maximum = std::max(maximum, std::abs(int(a[i]) - int(b[i])));
    }

    error = maximum;
}