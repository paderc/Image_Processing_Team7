#include <iostream>
#include <string>
#include "Brightness_Modifier.h"
#include "Negative_Modifier.h"

using namespace std;

string new_filename(const char original_filename[]) {
	const char BASIC_NAME_ADDON[] = "_mod";
	string original_string(original_filename);

	auto dot_index = original_string.find_first_of(".");
	return original_string.substr(0, dot_index) + BASIC_NAME_ADDON + original_string.substr(dot_index);
}

string new_filename(const char original_filename[], const char operation[], int value) {
	const char BASIC_NAME_ADDON[] = "_mod";
	string original_string(original_filename);

	auto dot_index = original_string.find_first_of(".");
	return original_string.substr(0, dot_index) + "_" + operation + to_string(value) + original_string.substr(dot_index);
}

void change_brightness(const char filename[], int brightness) {
	CImg<unsigned char> image;
	if (!image.load(filename)) {
		cout << "Did not find file at " << filename << endl;
		return;
	}
	cout << "Changing brightness of " << filename << " by " << brightness << endl;
	Brightness_Modifier().change(image, brightness);
	
	image.save(new_filename(filename).c_str());
}
void flip_negative(const char filename[]) {
	CImg<unsigned char> image;
	if (!image.load(filename)) {
		cout << "Did not find file at " << filename << endl;
		return;
	}
	Negative_Modifier().change(image);
	image.save(new_filename(filename).c_str());
}

void handle_args(int argc, char* argv[]) {
	if (argc > 1) {
		if (string(argv[1]) == "--brightness" && argc == 4) {
			
			change_brightness(argv[2], stoi(argv[3]));
		}
		else if (string(argv[1]) == "--negative" && argc == 3) {
			flip_negative(argv[2]);
		}
		else {
			cout << "Not doing anything" << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	handle_args(argc, argv);
	return 0;
}

