/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : William Escamilla
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 10/23/2020
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
	// TODO
	// DO NOT change the function header in any way.
	size_t j = left;
	for (size_t i = left + 1; i <= right; i++) {
		if (array[left] >= array[i]) {
			j++;
			swap(array[j], array[i]);
		}
	}

	swap(array[left], array[j]);
	return j;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
	// TODO
	// DO NOT change the function header in any way.
	size_t j = lomuto_partition(array, left, right);
	if (j == k - 1) {
		return array[j];
	} else if (j > k - 1) {
		return quick_select(array, left, j - 1, k);
	}

	return quick_select(array, j + 1, right, k);
}

int quick_select(int array[], const size_t length, size_t k) {
	return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <k>" << endl;
		return 1;
	}

	int k;
	istringstream iss;
	iss.str(argv[1]);
	if (!(iss >> k) || k <= 0) {
		cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
		return 1;
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	iss.clear();
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

	int num_values = values.size();
	if (num_values == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	// TODO - error checking k against the size of the input
	if (k > (int) num_values) {
		cerr << "Error: Cannot find smallest element " << k << " with only "
				<< num_values << ((num_values == 1) ? " value." : " values.")
				<< endl;
		return 1;
	}

	// TODO - call the quick_select function and display the result
	cout << "Smallest element " << k << ": "
			<< quick_select(&values[0], num_values, k) << endl;
	return 0;
}
