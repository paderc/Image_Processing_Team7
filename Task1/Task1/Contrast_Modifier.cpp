#include "Contrast_Modifier.h"
#include <algorithm>

using namespace cimg_library;

void Contrast_Modifier::change(CImg<unsigned char>& image, float contrast) {
	cimg_forXYC(image, x, y, c) {
		throw ERROR_CALL_NOT_IMPLEMENTED;
	}
}