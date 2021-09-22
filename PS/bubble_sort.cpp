
#include <iostream>
#include <stdlib.h>
#include <time.h>

void swap(int &a, int &b){
	a = a + b;
	b = a - b;
	a = a - b;
}

void bubble_sort(int *& arr, int length){
	for(int i = 0; i< length; i++) {
		bool swap_flag = false;
		for (int j = 0; j < length - 1; j++){
			if(arr[j] > arr[j+1]) {
				swap(arr[j],arr[j+1]);
				swap_flag = true; 
			}
		}
		if (!swap_flag) { break; }
	}
}

void fill(int *&arr, int length, int range) {
	for(int i = 0; i< length; i++) {
		arr[i] = rand() % range +1;
	}
	
}

void print(int *&arr, int length) {
	for(int i = 0; i< length; i++) {
		std::cout << arr[i] << "\n";
	}
}

int main() {

	int *arr = new int[10];
	fill(arr,10,10);
	std::cout << "Before sort: \n";
	print(arr,10);
	
	bubble_sort(arr,10);
	std::cout << "After sort: \n";
	print(arr,10);
	
	return 0;
}