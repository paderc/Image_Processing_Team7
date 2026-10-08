#include "Contrast_Modifier.h"
#include <algorithm>

using namespace cimg_library;

void Contrast_Modifier::modify() {
	int factor = (105 * (contrast + 100)) / (100 * (105 - contrast));
	cimg_forXYC(image, x, y, c) {
		image(x, y, c) = std::clamp(int(factor * (image(x, y, c) - 128) + 128), 0, 255);
	}
}