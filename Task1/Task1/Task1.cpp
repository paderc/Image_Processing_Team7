#include <iostream>
#include <string>
#include <chrono>
#include <string_view>

#include "Brightness_Modifier.h"
#include "Negative_Modifier.h"
#include "Contrast_Modifier.h"
#include "Rotation_Modifier.h"

#include "Info.cpp"

using namespace std;
using namespace cimg_library;

constexpr const char* Reset = "\033[0m";
constexpr const char* Red = "\033[31m";
constexpr const char* Green = "\033[32m";

void print_help_for(Modifier_Info cmd)
{
	cout << Red << "Use " << cmd.name << " " << cmd.details << Reset << endl;
}

void print_help_for(Measurer_Info cmd)
{
	cout << Red << "Use " << cmd.name << " " << cmd.details << Reset << endl;
}

void print_unknown_cmd() {
	cout << "Unknown Command" << endl << "Use --help for commands" << endl;
}
void print_help() {
	cout << Green << "Available commands" << Reset << endl;
	cout << Green << "---" << Reset << endl;
	for (const Modifier_Info& cmd : ALL_MODIFIERS) {
		cout << cmd.name << "  -  " << cmd.description << endl;
	}
	cout << Green << "---" << Reset << endl;
}
void handle_args(int argc, char* argv[]) {
	//Base command amount -> program, command
	unsigned short base_amt = 2;
	if (argc > 1) {
		string_view command(argv[1]);
		
		bool timer = false;
		bool verbose = false;

		for (int i = base_amt; i < argc; i++) {
			string_view s(argv[i]);
			if (s == "--timer" || s == "-t") timer = true;
			else if (s == "--verbose" || s == "-v") verbose = true;
		}

		for (const Modifier_Info& cmd : ALL_MODIFIERS) {
			if (command == cmd.name) {
				if (argc == base_amt + cmd.required_commands + timer + verbose) {
					auto modifier = cmd.factory(argv);

					modifier->init();

					modifier->modify(timer, verbose);

					modifier->image.save(modifier->filename.c_str());
					return;
				}
				else {
					print_help_for(cmd);
					return;
				}
			}
		}
		for (const Measurer_Info& cmd : ALL_MEASURERS) {
			if (command == cmd.name) {
				if (argc == base_amt + cmd.required_commands + timer + verbose) {
					auto measurer = cmd.factory(argv);

					measurer->measure(timer, verbose);
					return;
				}
				else {
					print_help_for(cmd);
					return;
				}
			}
		}
		if (command == "--help" || command == "-h") {
			print_help();
		}
		else {
			cout << Red << "Use --help or -h for commands" << Reset << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	handle_args(argc, argv);
	return 0;
}

