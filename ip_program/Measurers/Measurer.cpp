#include "Measurer.h"

#include <chrono>
#include <iostream>

using namespace std;
double Measurer::variance(const Intensity_Data& data) {
	double variance = 0.0;
	const double average = mean(data);
	for (size_t i = 0; i < data.occurences.size(); ++i) {
		const double centered = static_cast<double>(i) - average;
		variance += centered * centered * data.occurences[i];
	}
	const double pixels = static_cast<double>(width) * height;
	return pixels > 0 ? variance / pixels : 0.0;
}
double Measurer::mean(const Intensity_Data& data) {
	double sum = 0.0;

	for (size_t i = 0; i < data.occurences.size(); ++i) {
		sum += static_cast<double>(i) * data.occurences[i];
	}
	const double pixels = static_cast<double>(width) * height;
	return pixels > 0 ? sum / pixels : 0.0;
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
