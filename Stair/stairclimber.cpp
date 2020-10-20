/*******************************************************************************
 * Name    : stairclimber.cpp
 * Author  : William Escamilla
 * Version : 1.0
 * Date    : October 1, 2020
 * Description : Lists the number of ways to climb n stairs
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int> > get_ways(int num_stairs) {
	// TODO: Return a vector of vectors of ints representing
	// the different combinations of ways to climb num_stairs
	// stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;
	vector<vector<int>> result;
	if (num_stairs <= 0) {
		ways.push_back(vector<int>());
	} else {
		for (int i = 1; i < 4; i++) {
			if (num_stairs >= i) {
				result = get_ways(num_stairs - i);
				for (unsigned int j = 0; j < result.size(); j++) {
					result[j].insert(result[j].begin(), i);
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}

	return ways;
}

void display_ways(const vector<vector<int> > &ways) {
	// TODO: Display the ways to climb stairs by iterating over
	// the vector of vectors and printing each combination.
	int highest_label_width = 0;
	unsigned int num = ways.size();
	while (num >= 1) {
		highest_label_width++;
		num /= 10;
	}

	for (unsigned int i = 0; i < ways.size(); i++) {
		cout << setw(highest_label_width) << i + 1 << ". ";
		cout << "[";
		for (unsigned int j = 0; j < ways[i].size(); j++) {
			cout << ways[i][j];
			if (j != ways[i].size() - 1) {
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}
}

int num_digits(int num) {
	int count = 0;
	while (num >= 1) {
		count++;
		num /= 10;
	}
	return count;
}

int main(int argc, char *const argv[]) {
	istringstream iss;
	int stair_num;

	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	iss.str(argv[1]);

	if (!(iss >> stair_num) || stair_num <= 0) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	iss.clear();

	vector<vector<int>> ways = get_ways(stair_num);
	if (ways.size() == 1) {
		cout << "1 way to climb 1 stair." << endl;
	} else {
		cout << ways.size() << " ways to climb " << stair_num << " stairs."
				<< endl;
	}
	display_ways(ways);

	return 0;
}
