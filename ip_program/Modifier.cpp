#include <iostream>
#include <chrono>

#include "Modifier.h"

using namespace std;

string Modifier::make_name(string_view base_name, string_view extension) {
	return string(base_name).append("_modified").append(extension);
}
string Modifier::describe() {
	return string("Modified image ").append(filename);
}

void Modifier::modify(bool timer, bool verbose) {
	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	
	modify_inherited();

	if (timer) {
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		double ms = chrono::duration<double, milli>(end - start).count();
		cout << "Modification took " << ms << " ms\n";
	}
	if (verbose) {
		cout << describe() << endl;
	}
}
