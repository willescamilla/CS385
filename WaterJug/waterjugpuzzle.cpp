/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : William Escamilla
 * Version : 1.0
 * Date    : October 20, 2020
 * Description : Solves famous water jug puzzle scenarios
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
			a { _a }, b { _b }, c { _c }, directions { _directions }, parent {
					nullptr } {
	}

	void clear() {
		if (this->parent != nullptr) {
			this->parent->clear();
			this->parent = nullptr;
		}
		delete this;
	}

	State* clone() {
		State *clone = new State(this->a, this->b, this->c, this->directions);
		if (this->parent != nullptr) {
			clone->parent = this->parent->clone();
		}
		return clone;
	}

	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << directions << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

void waterjug(int capA, int capB, int capC, int goalA, int goalB, int goalC) {
	int jugA = 0, jugB = 0, jugC = capC;
	State ***matrix = new State**[capA + 1];

	for (int i = 0; i < capA + 1; i++) {
		matrix[i] = new State*[capB + 1];
		fill(matrix[i], matrix[i] + capB + 1, nullptr);
	}

	vector<State*> stateQueue;
	State *init = new State(jugA, jugB, jugC, "Initial state. ");
	stateQueue.push_back(init);

	while (!stateQueue.empty()) {
		State *curr = stateQueue.at(0);
		stateQueue.erase(stateQueue.begin());
		if (curr->a == goalA && curr->b == goalB && curr->c == goalC) {
			stack<State*> solutionStates;
			solutionStates.push(curr);
			while (curr->parent != nullptr) {
				curr = curr->parent;
				solutionStates.push(curr);
			}

			while (!solutionStates.empty()) {
				State *solution = solutionStates.top();
				solutionStates.pop();
				cout << solution->to_string() << endl;
				delete solution;
			}

			for (int i = 0; i < capA + 1; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			stateQueue.clear();

			/*while(!stateQueue.empty()){
			 delete stateQueue.at(0);
			 stateQueue.erase(stateQueue.begin());
			 }*/
			return;
		}

		if (matrix[curr->a][curr->b] == nullptr) {
			matrix[curr->a][curr->b] = curr;
			int newA, newB, newC;
			ostringstream oss;

			//Pour C to A
			if (curr->c != 0 && curr->a != capA) {
				if (capA >= (curr->a + curr->c)) {
					newA = curr->a + curr->c;
					newC = 0;
					newB = curr->b;
				} else {
					newC = curr->c - (capA - curr->a);
					newA = capA;
					newB = curr->b;
				}
				int diff = curr->c - newC;
				oss << "Pour " << diff << " gallon";
				if (diff != 1) {
					oss << "s";
				}
				oss << " from C to A. ";
				State *newNode = new State(newA, newB, newC,
						(string) oss.str());
				oss.str("");
				oss.clear();
				newNode->parent = curr->clone();
				stateQueue.push_back(newNode);
			}
			//Pour B to A
			if (curr->b != 0 && curr->a != capA) {
				if (capA >= (curr->a + curr->b)) {
					newA = curr->a + curr->b;
					newC = curr->c;
					newB = 0;
				} else {
					newC = curr->c;
					newA = capA;
					newB = curr->b - (capA - curr->a);
				}
				int diff = curr->b - newB;
				oss << "Pour " << diff << " gallon";
				if (diff != 1) {
					oss << "s";
				}
				oss << " from B to A. ";
				State *newNode = new State(newA, newB, newC, oss.str());
				oss.str("");
				oss.clear();
				newNode->parent = curr->clone();
				stateQueue.push_back(newNode);
			}
			//Pour C to B
			if (curr->c != 0 && curr->b != capB) {
				if (capB >= (curr->b + curr->c)) {
					newA = curr->a;
					newC = 0;
					newB = curr->b + curr->c;
				} else {
					newC = curr->c - (capB - curr->b);
					newA = curr->a;
					newB = capB;
				}
				int diff = curr->c - newC;
				oss << "Pour " << diff << " gallon";
				if (diff != 1) {
					oss << "s";
				}
				oss << " from C to B. ";
				State *newNode = new State(newA, newB, newC,
						(string) oss.str());
				oss.str("");
				oss.clear();
				newNode->parent = curr->clone();
				stateQueue.push_back(newNode);
			}
			//Pour A to B
			if (curr->a != 0 && curr->b != capB) {
				if (capB >= (curr->b + curr->a)) {
					newA = 0;
					newC = curr->c;
					newB = curr->b + curr->a;
				} else {
					newC = curr->c;
					newA = curr->a - (capB - curr->b);
					newB = capB;
				}
				int diff = curr->a - newA;
				oss << "Pour " << diff << " gallon";
				if (diff != 1) {
					oss << "s";
				}
				oss << " from A to B. ";
				State *newNode = new State(newA, newB, newC, oss.str());
				oss.str("");
				oss.clear();
				newNode->parent = curr->clone();
				stateQueue.push_back(newNode);
			}
			//Pour B to C
			if (curr->b != 0 && curr->c != capC) {
				if (capC >= (curr->c + curr->b)) {
					newA = curr->a;
					newC = curr->c + curr->b;
					newB = 0;
				} else {
					newC = capC;
					newA = curr->a;
					newB = curr->b - (capC - curr->c);
				}
				int diff = curr->b - newB;
				oss << "Pour " << diff << " gallon";
				if (diff != 1) {
					oss << "s";
				}
				oss << " from B to C. ";
				State *newNode = new State(newA, newB, newC, oss.str());
				oss.str("");
				oss.clear();
				newNode->parent = curr->clone();
				stateQueue.push_back(newNode);
			}
			//Pour A to C
			if (curr->a != 0 && curr->c != capC) {
				if (capC >= (curr->c + curr->a)) {
					newA = 0;
					newC = curr->c + curr->a;
					newB = curr->b;
				} else {
					newC = capC;
					newA = curr->a - (capC - curr->c);
					newB = curr->b;
				}
				int diff = curr->a - newA;
				oss << "Pour " << diff << " gallon";
				if (diff != 1) {
					oss << "s";
				}
				oss << " from A to C. ";
				State *newNode = new State(newA, newB, newC, oss.str());
				oss.str("");
				oss.clear();
				newNode->parent = curr->clone();
				stateQueue.push_back(newNode);
			}
		}
		curr->clear();
	}
//	for (int i = 0; i < capA + 1; i++) {
//		delete[] matrix[i];
//	}
//	delete[] matrix;
	cout << "No solution." << endl;
	return;
}

int main(int argc, char *argv[]) {
	//int capA = 3, capB = 5, capC = 8, goalA = 0, goalB = 5, goalC = 3;
	if (argc != 7) {
		cerr
				<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
				<< endl;
		return 1;
	}

	istringstream iss;
	int x, capA, capB, capC, goalA, goalB, goalC;
	iss.str(argv[1]);
	if (!(iss >> x) || x <= 0) {
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A."
				<< endl;
		return 1;
	} else {
		capA = x;
	}

	iss.clear();
	iss.str(argv[2]);
	if (!(iss >> x) || x <= 0) {
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B."
				<< endl;
		return 1;
	} else {
		capB = x;
	}

	iss.clear();
	iss.str(argv[3]);
	if (!(iss >> x) || x <= 0) {
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C."
				<< endl;
		return 1;
	} else {
		capC = x;
	}

	iss.clear();
	iss.str(argv[4]);
	if (!(iss >> x) || x < 0) {
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;

	}
	iss.clear();
	iss.str(argv[5]);
	if (!(iss >> x) || x < 0) {
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[6]);
	if (!(iss >> x) || x < 0) {
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;
	}

	iss.clear();
	iss.str(argv[4]);
	iss >> x;
	if (x > capA) {
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	} else {
		goalA = x;
	}

	iss.clear();
	iss.str(argv[5]);
	iss >> x;
	if (x > capB) {
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	} else {
		goalB = x;
	}

	iss.clear();
	iss.str(argv[6]);
	iss >> x;
	if (x > capC) {
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	} else {
		goalC = x;
	}

	iss.clear();
	if ((goalA + goalB + goalC) != capC) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return 1;
	}

	waterjug(capA, capB, capC, goalA, goalB, goalC);

	return 0;
}
