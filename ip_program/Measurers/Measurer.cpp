#include "Measurer.h"

#include <chrono>
#include <iostream>

using namespace std;
double Measurer::variance(Intensity_Data data) {
	double variance = 0.0;
	double mean = this->mean(data);
	for (int i = 0; i < data.occurences.size(); i++) {
		variance += (i - mean) * (i - mean) * data.occurences.at(i);
	}
	return variance / (image.width() * image.height());
}
double Measurer::mean(Intensity_Data data) {
	double score = 0.0;

	for (int i = 0; i < data.occurences.size(); i++) {
		score += i * data.occurences.at(i);
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