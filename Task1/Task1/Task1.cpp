#include <iostream>
#include <string>
#include "Brightness_Modifier.h"

using namespace std;

void change_brightness(const char filename[], int brightness) {
	CImg<unsigned char> image;
	if (!image.load(filename)) {
		return;
	}
	Brightness_Modifier().change(image, brightness);
	image.save(filename);
}

void handle_args(int argc, char* argv[]) {
	if (argc > 1) {
		if (argv[1] == "--brightness" && argc == 3) {
			change_brightness(argv[2], int(argv[3]));
		}
	}
}

int main(int argc, char* argv[]) {
	handle_args(argc, argv);
	return 0;
}

