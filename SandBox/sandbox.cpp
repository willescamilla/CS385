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

int mystery1(int a, int b) {
    int c = a - b,
        d = (c >> 7) & 1,
        mystery = a - c * d;
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

int mystery4(int n){
	return ((n)*(n+1)*(2*n+1))/6;
}
void mystery5(){
	int a = 11;
	cout << ( ((a << 3) | 14) >> (a & 23) ) << endl;
}

void shaker_sort(int array[], const int length) {
     int max_index = length, min_index = 1;
     bool sorted;
     do {
          sorted = true;
          for (int i = min_index; i < max_index; i++) {
               if (array[i - 1] > array[i]) {
            	   int temp = array[i];
            	   array[i] = array[i-1];
            	   array[i-1] = temp;
                    sorted = false;
               }
          }
          max_index--;
          if (sorted) break;
          for (int i = max_index - 1; i >= min_index; i--) {
               if (array[i - 1] > array[i]) {
            	   int temp = array[i];
            	   array[i] = array[i-1];
            	   array[i-1] = temp;
                    sorted = false;
               }
          }
          min_index++;
          for(int i = 0; i < length; i++){
        	  cout << array[i] << " ";
          }
     } while (!sorted);
}

vector<string> mystery(string &values){
	string v2;
	sort(values.begin(), values.end());
	return mystery_helper(values, v2);
}

vector<string> mystery_helper(string &v1, string&v2){
	vector<string> temp;
	if(v1.size() == 0){
		temp.push_back(v2);
		return temp;
	}

	for(size_t i = 0; i < v1.size(); ++i){
		char choice = v1[i];
		v1.erase(v1.begin() + i);
		v2.push_back(choice);

		vector<string> ret_val;
		retu_val = mystery_helper(v1, v2);
		temp.insert(temp.end(), ret_val.begin(), ret_val.end());

		v1.insert(v1.begin() + i, choice);
		v2.erase(v2.begin() + v2.size() - 1);
	}
	return temp;
}

int main(int argc, char *const argv[]){
//	int n;
//	istringstream iss;
//	iss.str(argv[1]);
//	iss >> n;
	string bum = "William";
	mystery(bum);

return 0;

}

