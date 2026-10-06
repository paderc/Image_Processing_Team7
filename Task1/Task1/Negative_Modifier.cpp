#include "Negative_Modifier.h"
#include <algorithm>
using namespace cimg_library;

void Negative_Modifier::change(CImg<unsigned char> &image) {
	cimg_forXYC(image, x, y, c) {
		image(x, y, c) = std::clamp(255 - image(x, y, c), 0, 255);
	}
}