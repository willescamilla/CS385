/*******************************************************************************
 * Name    : unique.cpp
 * Author  : William Escamilla
 * Version : 1.0
 * Date    : September 25, 2020
 * Description : Unique letters tester
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for(char const &letter : s){
		if(letter < 'a' || letter > 'z'){
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int bitset = 0;
	for(char const &letter: s){
		if(bitset & (1 << (letter-'a'))){
			return false;
		}
		bitset |= (1 << (letter - 'a'));
	}

	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}
	else if(!is_all_lowercase(argv[1])){
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	else if(!all_unique_letters(argv[1])){
		cout << "Duplicate letters found." << endl;
	}
	else{
		cout << "All letters are unique." << endl;
	}

	return 0;
}
