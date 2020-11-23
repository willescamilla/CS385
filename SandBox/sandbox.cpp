/*
 * sandbox.cpp
 *
 *  Created on: Sep 17, 2020
 *      Author: user
 */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

/*int mystery1(int a, int b) {
	int c = a - b, d = (c >> 7) & 1, mystery = a - c * d;
	return mystery;
}

int mystery2(int x) {
	return (x && !(x & (x - 1)));
}

int mystery3(int x, int y) {
	int s, c;
	s = x ^ y;
	c = x & y;
	while (c != 0) {
		c = c << 1;
		x = s;
		y = c;
		s = x ^ y;
		c = x & y;
	}
	return s;
}

int mystery4(int n) {
	return ((n) * (n + 1) * (2 * n + 1)) / 6;
}
void mystery5() {
	int a = 11;
	cout << (((a << 3) | 14) >> (a & 23)) << endl;
}

void shaker_sort(int array[], const int length) {
	int max_index = length, min_index = 1;
	bool sorted;
	do {
		sorted = true;
		for (int i = min_index; i < max_index; i++) {
			if (array[i - 1] > array[i]) {
				int temp = array[i];
				array[i] = array[i - 1];
				array[i - 1] = temp;
				sorted = false;
			}
		}
		max_index--;
		if (sorted)
			break;
		for (int i = max_index - 1; i >= min_index; i--) {
			if (array[i - 1] > array[i]) {
				int temp = array[i];
				array[i] = array[i - 1];
				array[i - 1] = temp;
				sorted = false;
			}
		}
		min_index++;
		for (int i = 0; i < length; i++) {
			cout << array[i] << " ";
		}
	} while (!sorted);
}

vector<string> mystery(string &values) {
	string v2;
	sort(values.begin(), values.end());
	return mystery_helper(values, v2);
}

vector<string> mystery_helper(string &v1, string &v2) {
	vector < string > temp;
	if (v1.size() == 0) {
		temp.push_back(v2);
		return temp;
	}

	for (size_t i = 0; i < v1.size(); ++i) {
		char choice = v1[i];
		v1.erase(v1.begin() + i);
		v2.push_back(choice);

		vector < string > ret_val;
		retu_val = mystery_helper(v1, v2);
		temp.insert(temp.end(), ret_val.begin(), ret_val.end());

		v1.insert(v1.begin() + i, choice);
		v2.erase(v2.begin() + v2.size() - 1);
	}
	return temp;
}*/

int main(int argc, char *const argv[]) {
//	int n;
//	istringstream iss;
//	iss.str(argv[1]);
//	iss >> n;
	// Read in the data and initialize the variables.
	int num_students;
	cin >> num_students;
	vector<int> mistakes(num_students);
	vector<int> steps(num_students);
	for (int i = 0; i < num_students; i++) {
		cin >> mistakes[i];
		steps[i] = 2;
	}
	// Make a forward pass, looking for students who should receive more steps
	// than those to the left.
	for (int i = 1; i < num_students; i++) {
		if (mistakes[i] > mistakes[i - 1]) {
			steps[i] = steps[i-1] + 1;  // What code is needed here?
		}
	}
	// Make a reverse pass, looking for students who should receive more steps
	// than those to the right.
	for (int i = num_students - 1; i > 0; i--) {
		if (mistakes[i - 1] > mistakes[i] && steps[i - 1] <= steps[i]) {
			steps[i - 1] = steps[i] + 1;  // What code is needed here?
		}
	}
	// Find the total number of steps.
	long sum = 0;
	for (int n : steps) {
		sum += n;
	}
	cout << sum << endl;
	return 0;

}

