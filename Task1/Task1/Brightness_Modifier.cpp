#include "Brightness_Modifier.h"
#include <algorithm>

void Brightness_Modifier::modify() {
	cimg_forXYC(image, x, y, c) {
		image(x, y, c) = std::clamp(image(x, y, c) + brightness, 0, 255);
	}
}