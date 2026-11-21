#include "Histogram.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdexcept>

Histogram::Histogram(char* argv[], int argc)
	: image(), filename(argv[2]), channel_arg(argc >= 4 ? argv[3] : "all"),
	  output_filename(argc >= 5 ? argv[4] : "histogram.bmp") {
	image.load(argv[2]);
}

void Histogram::make_inherited(Histogram_Data& data) {
	data.makeGraph(1024, 640, false).save(output_filename.c_str());
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
		int ch;
		if (channel_arg == "0" || channel_arg == "r" || channel_arg == "R") ch = 0;
		else if (channel_arg == "1" || channel_arg == "g" || channel_arg == "G") ch = 1;
		else if (channel_arg == "2" || channel_arg == "b" || channel_arg == "B") ch = 2;
		else throw std::invalid_argument("Choose 0, 1, 2, r, g, b, intensity, or all for the histogram channel.");
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
