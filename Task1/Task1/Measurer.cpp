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
	
	cout << "Error between " << filename1 << " and " << filename2 << " is " << error << " [pixel^2]" << endl;
}