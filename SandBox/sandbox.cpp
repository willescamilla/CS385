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



int main(int argc, char *const argv[]){
//	int n;
//	istringstream iss;
//	iss.str(argv[1]);
//	iss >> n;
	int bum[5] =  {2,1,9,7,6,};
	shaker_sort(bum, 5);

return 0;

}

