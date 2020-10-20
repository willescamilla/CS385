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

	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
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

	queue<State> stateQueue;
	State init(jugA, jugB, jugC, "Initial state. ");
	stateQueue.push(init);

	while (!stateQueue.empty()) {
		State *curr = &stateQueue.front();
		stateQueue.pop();
		if (curr->a == goalA && curr->b == goalB && curr->c == goalC) {
			stack<State> solutionStates;
			solutionStates.push(*curr);
			while (curr->parent != nullptr) {
				curr = curr->parent;
				solutionStates.push(*curr);
			}

			while (!solutionStates.empty()) {
				curr = &solutionStates.top();
				solutionStates.pop();
				cout << curr->directions << curr->to_string() << endl;
			}
			return;
		}

		if (matrix[curr->a][curr->b] == nullptr) {
			matrix[curr->a][curr->b] = curr;
			int newA, newB, newC;

			//Pour C to A
			if (curr->c != 0 && curr->a != capA) {
				if (capA >= (curr->a + curr->c)) {
					newA = curr->a + curr->c;
					newC = 0;
					newB = curr->b;
				} else {
					newC -= capA - curr->a;
					newA = capA;
					newB = curr->b;
				}
				string amtPoured = "" + curr->c - newC;
				State newNode(newA, newB, newC,
						"Pour " + amtPoured + " gallons from C to B. ");
				newNode.parent = curr;
				stateQueue.push(newNode);
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
					newB -= capA - curr->a;
				}
				string amtPoured = "" + curr->c - newC;
				State newNode(newA, newB, newC,
						"Pour " + amtPoured + " gallons from C to B");
				newNode.parent = curr;
				stateQueue.push(newNode);
			}
		}

	}
}

int main(int argc, char *argv[]) {
	State s(0, 0, 8, "Initial state.");
	cout << s.to_string() << endl;
	s.a += 3;
	s.c -= 3;
	cout << s.to_string() << endl;

	if (argc != 7) {
		cerr
				<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
				<< endl;
		return 1;
	}

	istringstream iss;
	int x, capA, capB, capC, goalA, goalB, goalC;
	iss.str(argv[1]);
	if (!(iss >> x) || x < 0) {
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A."
				<< endl;
		iss.clear();
		return 1;
	} else {
		capA = x;
		iss.clear();
	}
	iss.str(argv[2]);
	if (!(iss >> x) || x < 0) {
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B."
				<< endl;
		iss.clear();
		return 1;
	} else {
		capB = x;
		iss.clear();
	}
	iss.str(argv[3]);
	if (!(iss >> x) || x < 0) {
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C."
				<< endl;
		iss.clear();
		return 1;
	} else {
		capC = x;
		iss.clear();
	}

	iss.str(argv[4]);
	if (!(iss >> x)) {
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		iss.clear();
		return 1;

	} else if (x < 0 || x > capA) {
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		iss.clear();
		return 1;
	} else {
		goalA = x;
		iss.clear();
	}

	iss.str(argv[5]);
	if (!(iss >> x)) {
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		iss.clear();
		return 1;
	} else if (x < 0 || x > capB) {
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		iss.clear();
		return 1;
	} else {
		goalB = x;
		iss.clear();
	}

	iss.str(argv[6]);
	if (!(iss >> x)) {
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		iss.clear();
		return 1;
	} else if (x < 0 || x > capC) {
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		iss.clear();
		return 1;
	} else {
		goalC = x;
		iss.clear();
	}

	if ((goalA + goalB + goalC) != capC) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return 1;
	}

	waterjug(capA, capB, capC, goalA, goalB, goalC);

	return 0;
}
