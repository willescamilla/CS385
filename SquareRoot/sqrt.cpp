/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : William Escamilla
 * Version : 1.0
 * Date    : September 3, 2020
 * Description : Computes the square root of a double using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

double sqrt(double num, double epsilon= 1e-7) {
	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	} else if (num == 0 || num == 1) {
		return num;
	}

	double last_guess = num;
	double next_guess = (last_guess + num / last_guess) / 2;

	while (abs(last_guess - next_guess) > epsilon) {
		last_guess = next_guess;
		next_guess = (last_guess + num / last_guess) / 2;
	}

	return next_guess;
}

int main(int argc, char *const argv[]) {
	double m, n;
	istringstream iss;

	if (argc != 2 && argc != 3) {
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}
	iss.str(argv[1]);

	if (!(iss >> m)) {
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}

	iss.clear();
	if (argc == 3) {
		iss.str(argv[2]);
		if (!(iss >> n)) {
			cerr << "Error: Epsilon argument must be a double." << endl;
			return 1;
		}
		else if (n < 0 || -n*n == n) {
			cerr << "Error: Epsilon argument must be a positive double."
					<< endl;
			return 1;
		}

	}

	cout << fixed << setprecision(8) << sqrt(m, n) << endl;

}

