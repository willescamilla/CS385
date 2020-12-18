/*******************************************************************************
 * Name        : powergrid.cpp
 * Author      : William Escamilla
 * Version     : 1.0
 * Date        : 12/14/20
 * Description : Uses Prims's algorithim for finding the shortest path to power all intersections.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <climits>
#include <iomanip>
#include <string.h>
#include <list>
using namespace std;

struct Edge {
	int from, to;
	long weight;
	string streetName;
	Edge(int _from, int _to, long _weight, string _streetName) :
			from { _from }, to { _to }, weight { _weight }, streetName {
					_streetName } {
	}
};

long INF = LONG_MAX;
int num_vertices;
vector<Edge> minheap;
vector<list<Edge>> adj_list;

void printHeap() {
	for (size_t i = 0; i < minheap.size(); i++) {
		cout << "Node " << i << ": From: " << minheap[i].from << " To: "
				<< minheap[i].to << " Weight: " << minheap[i].weight
				<< " Name: " << minheap[i].streetName << endl;
	}
}

void initializeHeap() {
	for (int i = 1; i <= num_vertices; i++) {
		Edge temp(0, i, INF, "");
		minheap.push_back(temp);
	}
}

void initializeList() {
	adj_list.resize(num_vertices+1);
}

void bubbleUp(int index) {
	if (index == 0) {
		return;
	}

	int parentIndex = (index - 1) / 2;
	if (minheap[parentIndex].weight > minheap[index].weight) {
		Edge temp = minheap[parentIndex];
		minheap[parentIndex] = minheap[index];
		minheap[index] = temp;
		bubbleUp(parentIndex);
	}
}

void bubbleDown(int index) {
	unsigned int length = minheap.size();
	unsigned int leftChildIndex = 2 * index + 1;
	unsigned int rightChildIndex = 2 * index + 2;

	if (leftChildIndex >= length)
		return; //index is a leaf

	int minIndex = index;

	if (minheap[index].weight > minheap[leftChildIndex].weight) {
		minIndex = leftChildIndex;
	}

	if ((rightChildIndex < length)
			&& (minheap[minIndex].weight > minheap[rightChildIndex].weight)) {
		minIndex = rightChildIndex;
	}

	if (minIndex != index) {
		//need to swap
		Edge temp = minheap[index];
		minheap[index] = minheap[minIndex];
		minheap[minIndex] = temp;
		bubbleDown(minIndex);
	}
}

void updateHeap(Edge newLad) {
	// Find the vertex in our heap that is the same vertex as newLad
	// If it's weight is less than newLad's, have newLad replace that edge in the heap
	// Then figure out if this new edge has to be bubbled up or down depending on it's
	// parent and children vertices and weights
	size_t parentIndex;
	size_t leftChildIndex;
	for (size_t i = 0; i < minheap.size(); i++) {
		if (minheap[i].to == newLad.to && minheap[i].weight > newLad.weight) {
			minheap[i] = newLad;
			parentIndex = (i - 1) / 2;
			leftChildIndex = 2 * i + 1;
			if (parentIndex >= 0
					&& ((newLad.weight < minheap[parentIndex].weight)
							|| ((newLad.weight == minheap[parentIndex].weight)
									&& (newLad.to < minheap[parentIndex].to)))) {
				bubbleUp(i);
			} else if (leftChildIndex < minheap.size()
					&& ((newLad.weight > minheap[leftChildIndex].weight))) {
				bubbleDown(i);
			}
			break;
		}
	}
}

Edge getMin() {
	return minheap[0];
}

void deleteMin() {
	size_t length = minheap.size();
	if (length == 0) {
		return;
	}

	minheap[0] = minheap[length - 1];
	minheap.pop_back();
	bubbleDown(0);
}

void addEdge(int from, int to, int weight, string streetName) {
	Edge temp(from, to, weight, streetName);
	adj_list[from].push_back(temp);
}

bool allVisited(vector<bool> beenVisited) {
	for (bool b : beenVisited) {
		if (b == false) {
			return false;
		}
	}

	return true;
}

bool compare_by_name(const Edge& lhs, const Edge& rhs){
	return lhs.streetName < rhs.streetName;
}

void print(vector<Edge> solutionStack, long wireLength) {
	cout << "Total wire length (meters): " << wireLength << endl;
	sort(solutionStack.begin(), solutionStack.end(), compare_by_name);
	for (Edge e : solutionStack) {
		cout << e.streetName << " [" << e.weight << "]" << endl;
	}
}

void powerGrid() {
	int currVertex = 1;
	long wireLength = 0;
	vector<Edge> solutionStack;
	vector<bool> beenVisited(num_vertices, false);
	beenVisited[0] = true;

	while (!allVisited(beenVisited)) {
		for (Edge x : adj_list[currVertex]) {
			updateHeap(x);
		}
		if(getMin().weight == INF){
			cout << "No solution." << endl;
			return;
		}
		Edge currEdge = getMin();
		currVertex = currEdge.to;
		wireLength += currEdge.weight;
		beenVisited[currVertex - 1] = true;

		solutionStack.push_back(currEdge);
		//cout << "Next Vertex: " << currVertex << endl;
		//printHeap();
		deleteMin();
	}

	print(solutionStack, wireLength);

}

int main(int argc, char *const argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input file>" << endl;
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
	vector<int> commaPos;
	string substr;
	int x;

	if (num_vertices < 1 || num_vertices > 1000) {
		cerr << "Error: Invalid number of vertices '" << line << "' on line 1."
				<< endl;
		return 1;
	}

	initializeHeap();
	initializeList();
	lineCount++;

	while (getline(file, line)) {
		// Make sure number of commas is equal to 3, if not, throw error
		for (unsigned int i = 0; i < line.size(); i++) {
			if (line[i] == ',') {
				commaPos.push_back(i);
			}
		}
		if (commaPos.size() != 3) {
			cerr << "Error: Invalid edge data '" << line << "' on line "
					<< lineCount << "." << endl;
			return 1;
		}

		// Create a substring of everything up to the first comma. Should be the starting vertex
		substr = line.substr(0, commaPos[0]);
		iss.clear();
		iss.str(substr);
		if (!(iss >> x) || stoi(substr) < 1 || stoi(substr) > num_vertices) {
			cerr << "Error: Starting vertex '" << substr << "' on line "
					<< lineCount << " is not among valid values 1-"
					<< num_vertices << "." << endl;
			return 1;
		}

		//Create a substring from the first comma to the second. This is the ending vertex
		substr = line.substr(commaPos[0] + 1, commaPos[1] - commaPos[0] - 1);
		iss.clear();
		iss.str(substr);
		if (!(iss >> x) || stoi(substr) < 1 || stoi(substr) > num_vertices) {
			cerr << "Error: Ending vertex '" << substr << "' on line "
					<< lineCount << " is not among valid values 1-"
					<< num_vertices << "." << endl;
			return 1;
		}

		//Create a substring from the second comma to the third. This is the edge weight
		substr = line.substr(commaPos[1] + 1, commaPos[2] - commaPos[1] - 1);
		iss.clear();
		iss.str(substr);
		if (!(iss >> x) || stoi(substr) < 1) {
			cerr << "Error: Invalid edge weight '" << substr << "' on line "
					<< lineCount << "." << endl;
			return 1;
		}

		addEdge(stoi(line.substr(0, commaPos[0])),
				stoi(
						line.substr(commaPos[0] + 1,
								commaPos[1] - commaPos[0] - 1)),
				stoi(
						line.substr(commaPos[1] + 1,
								commaPos[2] - commaPos[1] - 1)),
				line.substr(commaPos[2] + 1, line.npos));

		lineCount++;
		commaPos.clear();
	}

	//printHeap();
	powerGrid();

}

