/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : William Escamilla & Danielle Faustino
 * Version     : 1.0
 * Date        : 12/06/20
 * Description : Uses Floyd's algorithim for finding the shortest path in a graph.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <climits>
#include <iomanip>

long INF = LONG_MAX;
int num_vertices;
using namespace std;

int num_digits(long int num) {
	int count = 0;
	while (num >= 1) {
		count++;
		num /= 10;
	}
	return count;
}

/**  * Displays the matrix on the screen formatted as a table. */
void display_table(vector<vector<long int>> const matrix, const string &label,
		const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width =
			use_letters ?
					num_digits(max_val) :
					num_digits(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

void display_intermed_vertices(vector<vector<char>> const matrix,
		const string &label, const bool use_letters = false) {
	cout << label << endl;
	int max_cell_width = 1;
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == -1) {
				cout << "-";
			} else {
				cout << static_cast<char>(matrix[i][j] + 'A');
			}
		}
		cout << endl;
	}
	cout << endl;
}

void buildMatrix(vector<vector<long int>> *distMatrix) {
	for (long int i = 0; i < num_vertices; i++) {
		distMatrix->push_back( { });
		for (long int j = 0; j < num_vertices; j++) {
			if (i == j) {
				distMatrix->at(i).push_back(0);
			} else {
				distMatrix->at(i).push_back(INF);
			}
		}
	}

}

void buildIntermed(vector<vector<char>> *intermedMatrix) {
	for (long int i = 0; i < num_vertices; i++) {
		intermedMatrix->push_back( { });
		for (long int j = 0; j < num_vertices; j++) {
			intermedMatrix->at(i).push_back(-1);
		}
	}

}

void insertEdge(vector<vector<long int>> *distMatrix, int from, int to,
		string edgeLength) {
	from -= 65;
	to -= 65;
	distMatrix->at(from).at(to) = stol(edgeLength);
}

void floydsAlgo(vector<vector<long int>> *pathMatrix,
		vector<vector<char>> *intermedMatrix) {
	long currentVal;
	for (int k = 0; k < num_vertices; ++k) {
		for (int i = 0; i < num_vertices; ++i) {
			for (int j = 0; j < num_vertices; ++j) {
				currentVal = pathMatrix->at(i).at(j);
				if (pathMatrix->at(i).at(k) == INF
						|| pathMatrix->at(k).at(j) == INF
						|| pathMatrix->at(i).at(k) + pathMatrix->at(k).at(j)
								< 0) {
					pathMatrix->at(i).at(j) = pathMatrix->at(i).at(j);

				} else {
					pathMatrix->at(i).at(j) = min(pathMatrix->at(i).at(j),
							pathMatrix->at(i).at(k) + pathMatrix->at(k).at(j));
				}
				if (currentVal != pathMatrix->at(i).at(j)) {
					intermedMatrix->at(i).at(j) = k;
				}
			}
		}
	}
}

string findPath(vector<vector<long int>> pathMatrix,
		vector<vector<char>> intermedMatrix, int from, int to, bool isComplex) {
	string path;
	if (!isComplex) {
		path.push_back(from + 'A');
	}
	if (intermedMatrix[from][to] != -1) {
		path.append(
				findPath(pathMatrix, intermedMatrix, from,
						intermedMatrix[from][to], true));
		path.append(" -> ");
		path.push_back((intermedMatrix[from][to] + 'A'));
		path.append(
				findPath(pathMatrix, intermedMatrix, intermedMatrix[from][to],
						to, true));
	}
	if (!isComplex && from != to) {
		path.append(" -> ");
		path.push_back(to + 'A');
	}

	return path;
}

int main(int argc, char *const argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}
	fstream file;
	file.open(argv[1], ios::in);
	if (file.fail()) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}

	istringstream iss;
	string line;
	getline(file, line);
	iss.str(line);
	iss >> num_vertices;

	int lineCount = 1;
	char lastChar = 'A';
	vector<vector<long int>> distMatrix;

	if (num_vertices < 1 || num_vertices > 26) {
		cerr << "Error: Invalid number of vertices '" << line << "' on line 1."
				<< endl;
		return 1;
	} else {
		lastChar = 'A' + num_vertices - 1;
		buildMatrix(&distMatrix);
		lineCount++;
	}

	while (getline(file, line)) {
		if (line.size() < 5) {
			cerr << "Error: Invalid edge data '" << line << "' on line "
					<< lineCount << "." << endl;
			return 1;
		} else if (line[0] < 'A' || line[0] > lastChar || line[1] != ' ') {
			cerr << "Error: Starting vertex '" << line.substr(0, line.find(' '))
					<< "' on line " << lineCount
					<< " is not among valid values A-" << lastChar << "."
					<< endl;
			return 1;
		} else if (line[2] < 'A' || line[2] > lastChar || line[3] != ' ') {
			cerr << "Error: Ending vertex '"
					<< line.substr(2, line.find_last_of(' ') - 2)
					<< "' on line " << lineCount
					<< " is not among valid values A-" << lastChar << "."
					<< endl;
			return 1;
		} else if (line[4] == '-' || line[4] == '0' || !(isdigit(line[4]))) {
			cerr << "Error: Invalid edge weight '" << line.substr(4, line.npos)
					<< "' on line " << lineCount << "." << endl;
			return 1;
		} else {
			insertEdge(&distMatrix, line[0], line[2],
					line.substr(4, line.npos));
		}

		lineCount++;
	}

	vector<vector<long int>> pathMatrix = distMatrix;
	vector<vector<char>> intermedMatrix;
	buildIntermed(&intermedMatrix);

	floydsAlgo(&pathMatrix, &intermedMatrix);
	display_table(distMatrix, "Distance matrix:");
	display_table(pathMatrix, "Path lengths:");
	display_intermed_vertices(intermedMatrix, "Intermediate vertices:");

	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", distance: ";
			if (pathMatrix[i][j] == INF) {
				cout << "infinity, path: none" << endl;
			} else {

				cout << pathMatrix[i][j] << ", path: " << findPath(pathMatrix, intermedMatrix, i, j, false)
						<< endl;
			}
		}
	}

}

