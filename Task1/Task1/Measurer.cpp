#include <chrono>
#include <iostream>

#include "Measurer.h"

string Measurer::describe() {
	return string("Measuring error between ").append(filename1).append(" and ").append(filename2);
}
void Measurer::measure(bool timer, bool verbose) {
	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	
	measure_inherited();

	if (timer) {
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		double ms = chrono::duration<double, milli>(end - start).count();
		cout << "Modification took " << ms << " ms\n";
	}
	if (verbose) {
		cout << describe() << endl;
	}
	
	cout << "Error between " << filename1 << " and " << filename2 << " is " << error << unit << endl;
}
double Measurer::squared_error_sum() const {
	const auto* a = image1.data();
	const auto* b = image2.data();
	const auto count = image1.size();

	double sum = 0.0;

	for (decltype(image1.size()) i = 0; i < count; ++i) {
		const int difference = int(a[i]) - int(b[i]);
		sum += double(difference) * difference;
	}

	return sum;
}
double Measurer::reference_peak() const {
	const auto* values = image1.data();
	const auto count = image1.size();

	unsigned char peak = 0;

	for (decltype(image1.size()) i = 0; i < count; ++i)
	{
		if (values[i] > peak) peak = values[i];
	}

	return peak;
}