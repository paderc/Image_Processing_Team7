#include <exception>
#include <iostream>
#include <string_view>
#include <vector>

#include "Info.h"
#include "Histograms/Histogram.h"
#include "Histograms/Histogram_Data.h"

using namespace std;
using namespace cimg_library;

constexpr const char* Reset = "\033[0m";
constexpr const char* Red = "\033[31m";
constexpr const char* Green = "\033[32m";

template <class T>
void print_help_for(Command_Info<T> cmd)
{
	cout << Red << "Use " << cmd.name << " " << cmd.details << Reset << endl;
}

void print_unknown_cmd() {
	cout << "Unknown Command" << endl << "Use --help for commands" << endl;
}

void print_help() {
	cout << Green << "Available commands" << Reset << endl;
	cout << Green << "---" << Reset << endl;
	cout << "--histogram  -  Saves histogram of chosen channel ([filename] [0|1|2|r|g|b|intensity|all] [optional_output.bmp])" << endl;
	for (const Modifier_Info& cmd : ALL_MODIFIERS) {
		cout << cmd.name << "  -  " << cmd.description << endl;
	}
	for (const Comparator_Info& cmd : ALL_COMPARATORS) {
		cout << cmd.name << "  -  " << cmd.description << endl;
	}
	for (const Measurer_Info& cmd : ALL_MEASURERS) {
		cout << cmd.name << "  -  " << cmd.description << endl;
	}
	cout << Green << "---" << Reset << endl;
}

void handle_args(int argc, char* argv[]) {
	constexpr int base_amt = 2;
	if (argc > 1) {
		string_view command(argv[1]);

		bool timer = false;
		bool verbose = false;
		vector<char*> positional(argv, argv + base_amt);

		for (int i = base_amt; i < argc; i++) {
			string_view s(argv[i]);
			if (s == "--timer" || s == "-t") {
				timer = true;
			}
			else if (s == "--verbose" || s == "-v") {
				verbose = true;
			}
			else {
				positional.push_back(argv[i]);
			}
		}
		const int positional_count = static_cast<int>(positional.size()) - base_amt;

		if (command == "--histogram") {
			if (positional_count >= 1 && positional_count <= 3) {
				Histogram hist(positional.data(), positional_count + base_amt);
				hist.make(timer, verbose);
				return;
			}
			else {
				cout << Red << "Use --histogram [filename] [0|1|2|r|g|b|intensity|all] [optional_output.bmp]" << Reset << endl;
				return;
			}
		}

		for (const Modifier_Info& cmd : ALL_MODIFIERS) {
			if (command == cmd.name) {
				if (positional_count == cmd.required_commands) {
					auto modifier = cmd.factory(positional.data());

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
		for (const Comparator_Info& cmd : ALL_COMPARATORS) {
			if (command == cmd.name) {
				if (positional_count == cmd.required_commands) {
					auto comparator = cmd.factory(positional.data());

					comparator->compare(timer, verbose);
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
				if (positional_count == cmd.required_commands) {
					auto measurer = cmd.factory(positional.data());

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
	try {
		handle_args(argc, argv);
	}
	catch (const std::exception& error) {
		std::cerr << "Error: " << error.what() << '\n';
		return 1;
	}
	return 0;
}
