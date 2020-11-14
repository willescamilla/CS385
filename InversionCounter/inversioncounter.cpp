/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : William Escamilla
 * Version     : 1.0
 * Date        : 10/26/20
 * Description : Uses mergesort to count the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * invCounts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	// TODO
	long int invCount = 0;
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (array[j] < array[i]) {
				invCount++;
			}
		}
	}
	return invCount;
}

/**
 * invCounts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	// TODO
	// Hint: Use mergesort!
	int *scratch = new int[length];
	long int invinvCount = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;
	return invinvCount;
}

static long mergesort(int array[], int scratch[], int low, int high) {
	// TODO
	long int invCount = 0;
	if (low < high) {
		int mid = low + (high - low) / 2;
		invCount += mergesort(array, scratch, low, mid);
		invCount += mergesort(array, scratch, mid + 1, high);
		int newLow = low;
		int newHigh = mid + 1;
		int k = low;
		do {
			if (newLow <= mid
					&& (newHigh > high || array[newLow] <= array[newHigh])) {
				scratch[k] = array[newLow];
				newLow++;
			} else {
				scratch[k] = array[newHigh++];
				invCount += (mid - newLow + 1);
			}
			k++;
		} while (k <= high);

		k = low;
		do {
			array[k] = scratch[k];
			k++;
		} while (k <= high);
	}
	return invCount;
}

int main(int argc, char *argv[]) {
	// TODO: parse command-line argument
	istringstream iss;
	string option;
	if(argc > 2){
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}
	if(argc == 2){
		iss.str(argv[1]);
		iss >> option;
		if(option != "" && option != "slow"){
			cerr << "Error: Unrecognized option '" << option << "'." << endl;
			return 1;
		}
	}
	iss.clear();

	cout << "Enter sequence of integers, each followed by a space: " << flush;

	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}
	iss.clear();

	// TODO: produce output
	long int output;
	if (values.size() == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	if (option == "slow") {
		output = count_inversions_slow(&values[0], values.size());
	}
	else {
		output = count_inversions_fast(&values[0], values.size());
	}
	cout << "Number of inversions: " << output << endl;
	return 0;
}
