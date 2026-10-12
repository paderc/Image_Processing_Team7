#include "Rotation_Modifier.h"

void Rotation_Modifier::modify_inherited() {
	int H = image._height;
	int W = image._width;
	int S = image._spectrum;
	if (direction == "--dflip") {
		for (int y = 0; y < H; ++y) {
			for (int x = 0; x < W; ++x) {
				int xr = W - 1 - x;
				int yr = H - 1 - y;
				if (y > yr) continue;
				if (y == yr && x >= xr) continue;
				for (int c = 0; c < S; ++c) {
					unsigned char tmp = image(x, y, 0, c);
					image(x, y, 0, c) = image(xr, yr, 0, c);
					image(xr, yr, 0, c) = tmp;
				}
			}
		}
	}
	else if (direction == "--hflip") {
		int half = W / 2;
		for (int y = 0; y < H; ++y) {
			for (int x = 0; x < half; ++x) {
				int xr = W - 1 - x;
				for (int c = 0; c < S; ++c) {
					unsigned char tmp = image(x, y, 0, c);
					image(x, y, 0, c) = image(xr, y, 0, c);
					image(xr, y, 0, c) = tmp;
				}
			}
		}
	}
	else if (direction == "--vflip") {
		int half = H / 2;
		for (int x = 0; x < W; ++x) {
			for (int y = 0; y < half; ++y) {
				int yr = H - 1 - y;
				for (int c = 0; c < S; ++c) {
					unsigned char tmp = image(x, y, 0, c);
					image(x, y, 0, c) = image(x, yr, 0, c);
					image(x, yr, 0, c) = tmp;
				}
			}
		}
	}
}
