#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>

#include "Brightness_Modifier.h"
#include "Negative_Modifier.h"
#include "Contrast_Modifier.h"

#include "Cmd_Info.cpp"

using namespace std;
using namespace cimg_library;

constexpr const char* Reset = "\033[0m";
constexpr const char* Red = "\033[31m";

void print_help_for(Cmd_Info cmd)
{
	cout << Red << "Use " << cmd.name << " " << cmd.details << Reset << endl;
}

void print_unknown_cmd() {
	cout << "Unknown Command" << endl << "Use --help for commands" << endl;
}
void print_help() {
	cout << "Available commands" << endl;
	for (auto& cmd : ALL_COMMANDS) {
		cout << cmd.name << "  -  " << cmd.description << endl;
	}
}
void save_file(CImg<unsigned char>& image, const char *filename) {
	if (!image.save(filename)) {
		
		string new_filename(filename);
		new_filename += "_new";

		image.save(new_filename.c_str());
	}
}

string new_filename(const char original_filename[]) {
	const char BASIC_NAME_ADDON[] = "_mod";
	string original_string(original_filename);

	auto dot_index = original_string.find_first_of(".");
	return original_string.substr(0, dot_index) + BASIC_NAME_ADDON + original_string.substr(dot_index);
}

string new_filename(const char original_filename[], const char* operation, int value) {	
	string original_string(original_filename);

	auto dot_index = original_string.find_first_of(".");
	return original_string.substr(0, dot_index) + "_" + operation + to_string(value) + original_string.substr(dot_index);
}
string new_filename(const char original_filename[], const char* operation) {
	string original_string(original_filename);

	auto dot_index = original_string.find_first_of(".");
	return original_string.substr(0, dot_index) + "_" + operation + original_string.substr(dot_index);
}

//void change_brightness(const char filename[], int brightness) {
//	CImg<unsigned char> image;
//	if (!try_get_file(filename, &image)) return;
//	cout << "Changing brightness of " << filename << " by " << brightness;
//	Brightness_Modifier().change(image, brightness);
//	image.save(new_filename(filename, "brightness", brightness).c_str());
//}
//void flip_negative(const char filename[]) {
//	CImg<unsigned char> image;
//	if (!try_get_file(filename, &image)) return;
//	cout << "Flipping " << filename << " to its negative";
//	Negative_Modifier().change(image);
//	image.save(new_filename(filename, "negative").c_str());
//}
//void change_contrast(const char filename[], float contrast) {
//	CImg<unsigned char> image;
//	if (!try_get_file(filename, &image)) return;
//	cout << "Changing contrast of " << filename << " by " << contrast;
//	Contrast_Modifier().change(image, contrast);
//	image.save(new_filename(filename, "contrast", contrast).c_str());
//}
//void flip_horizontally(const char filename[]) {
//	CImg<unsigned char> image;
//	if (!try_get_file(filename, &image)) return;
//	cout << "Flipping " << filename << " horizontally" << endl;
//	Flip_Modifier(image).horizontal();
//	image.save(new_filename(filename, "hflip").c_str());
//}
//void flip_vertically(const char filename[]) {
//	CImg<unsigned char> image;
//	if (!try_get_file(filename, &image)) return;
//	cout << "Flipping " << filename << " vertically" << endl;
//	Flip_Modifier(image).vertical();
//	image.save(new_filename(filename, "vflip").c_str());
//}

void handle_args(int argc, char* argv[]) {
	//Base command amount -> program, command
	unsigned short base_amt = 2;
	if (argc > 1) {
		string command(argv[1]);
		for (const Cmd_Info& cmd : ALL_COMMANDS) {
			if (command == cmd.name) {
				if (argc == base_amt + cmd.number_required) {
					auto modifier = cmd.factory(argv);
					
					auto start = std::chrono::steady_clock::now();

					modifier->modify();
					
					auto end = std::chrono::steady_clock::now();

					modifier->save(new_filename(argv[2]).c_str());

					
					auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
					std::cout << "modify() took " << ms << " ms\n";
				}
				else {
					print_help_for(cmd);
				}
				return;
			}
		}
		if (command == "--help" || command == "-h") {
			print_help();
		}
		else {
			cout << "Use --help or -h for commands" << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	handle_args(argc, argv);
	return 0;
}

