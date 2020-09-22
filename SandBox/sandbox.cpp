/*
 * sandbox.cpp
 *
 *  Created on: Sep 17, 2020
 *      Author: user
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

void function1(int n) {
	int counter = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += 2) {
			counter++;
		}
	}

	cout << counter << endl;
}

int main(){
	//function1(1000);
	int x = 8;
	int y = 0;
	int count = 0;
	while(x >= y){
		count++;
		x = 5*(count*count) + 4*count + 8;
		y = 6*(count*count);
	}
	cout << count << endl;



}

