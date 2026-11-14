#include "Histogram.h"
#include <algorithm>
#include <chrono>
#include <iostream>

Histogram::Histogram(char* argv[], int argc)
	: image(), filename(argv[2]), channel_arg("all"), output_filename("histogram.bmp") {
	image.load(argv[2]);
	if (argc >= 4) {
		string arg3(argv[3]);
		if (arg3 != "--timer" && arg3 != "-t" && arg3 != "--verbose" && arg3 != "-v") {
			channel_arg = arg3;
		}
	}
	if (argc >= 5) {
		string arg4(argv[4]);
		if (arg4 != "--timer" && arg4 != "-t" && arg4 != "--verbose" && arg4 != "-v") {
			output_filename = arg4;
		}
	}
}

void Histogram::make_inherited(Histogram_Data& data) {
	CImg<unsigned char> chart = data.makeGraph(1024, 640, false);
	if (output_filename != "histogram.bmp") {
		chart.save(output_filename.c_str());
	}
}

void Histogram::make(bool timer, bool verbose) {
	if (verbose) {
		cout << "Generating histogram for " << filename << " (channel: " << channel_arg << ")" << endl;
	}
	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	if (channel_arg == "all") {
		Divided_Data data(image);
		make_inherited(data);
	}
	else if (channel_arg == "intensity" || channel_arg == "gray" || channel_arg == "grey") {
		Intensity_Data data(image);
		make_inherited(data);
	}
	else {
		int ch = 0;
		if (channel_arg == "1" || channel_arg == "g" || channel_arg == "G") ch = 1;
		else if (channel_arg == "2" || channel_arg == "b" || channel_arg == "B") ch = 2;
		ch = std::clamp(ch, 0, image.spectrum() - 1);

		CImg<unsigned char> single_channel = image.get_channel(ch);
		Divided_Data data(single_channel);
		make_inherited(data);
	}

	if (timer) {
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		double ms = chrono::duration<double, milli>(end - start).count();
		cout << "Histogram generation took " << ms << " ms\n";
	}
}
