#include "Measurer.h"
#include "../Histograms/Histogram_Data.h"

#include <chrono>
#include <iostream>

using namespace std;
double Measurer::variance() {
	double variance = 0.0;
	Intensity_Data intensity_data(image);
	double mean = this->mean();
	for (int i = 0; i < intensity_data.occurences.size(); i++) {
		variance += (i - mean) * (i - mean) * intensity_data.occurences.at(i);
	}
	return variance / (image.width() * image.height());
}
double Measurer::mean() {
	Intensity_Data intensity_data(image);
	double score = 0.0;

	for (int i = 0; i < intensity_data.occurences.size(); i++) {
		score += i * intensity_data.occurences.at(i);
	}
	return score / (image.width() * image.height());
}

string Measurer::describe() {
	return string("Measuring ").append(filename);
}
void Measurer::measure(bool timer, bool verbose) {
	if (verbose) {
			cout << describe() << endl;
	}
	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	measure_inherited();
	
	if (timer) {
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		double ms = chrono::duration<double, milli>(end - start).count();
		cout << "Measurement took " << ms << " ms\n";
	}

	cout << "Score of " << filename << " is " << score << unit << endl;
}