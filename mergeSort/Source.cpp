/*
Ellie Chen
CSC 382 - HW #1
*/

#include <iostream>
#include <array>
#include <ctime>
#include <stdlib.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


int* merge(int A[], int a_size, int B[], int b_size);
int* mergeSort(int A[], int arrayLength);

int main() {
	int A[10];
	int* sorted;

	int i, j;
	srand(time(0) + 5);

	cout << "MERGE SORT" << endl;

	//Populate array
	for (int i = 0; i < (sizeof(A)/sizeof(*A)); i++) {
		A[i] = (rand() % (sizeof(A) / sizeof(*A))) + 1;
	}

	//cout array before sort
	cout << "Before sort: ";
	for (int i = 0; i < (sizeof(A) / sizeof(*A)); i++) {
		cout << A[i] << " ";
	}
	cout << endl;

	/*
	* MERGE SORT
	*/
	auto start = high_resolution_clock::now();
	sorted = mergeSort(A, 10);
	auto end = high_resolution_clock::now();
	auto diff = duration_cast<microseconds>(end - start);

	//cout array after sort
	cout << "After sort: ";
	for (int i = 0; i < (sizeof(A) / sizeof(*A)); i++) {
		cout << sorted[i] << " ";
	}
	cout << endl;

	//cout time
	cout << "Time taken: " << diff.count() << endl;

	system("pause");
	return 0;


}

int* merge(int A[], int a_size, int B[], int b_size) {
	int holderSize = a_size + b_size;
	int * holder = new int[holderSize];
	int a_i = 0, b_i = 0;
	for (int i = 0; i < holderSize; i++) {
		if ((A[a_i] <= B[b_i] || b_i >= b_size) && a_i < a_size) { //Must check not going "out-of-bounds" because C++ is too dumb to have length property on arrays
			holder[i] = A[a_i];
			a_i++;
		}
		else if (b_i < b_size) {
			holder[i] = B[b_i];
			b_i++;
		}
	}

	return holder;
}

int* mergeSort(int A[], int arrayLength) {
	int arrayMiddle = arrayLength / 2;
	int* left, *right;

	//Split until arr size = 1 (recursion)
	if (arrayLength == 1)
		return A;
	else {
		//Split
		//POPULATE LEFT
		left = new int[arrayMiddle];
		for (int i = 0, j = 0; i < arrayMiddle; i++, j++) {
			left[j] = A[i];
		}

		//POPULATE RIGHT
		right = new int[arrayLength - arrayMiddle];
		for (int i = arrayMiddle, j = 0; i < arrayLength; i++, j++) {
			right[j] = A[i];
		}

		//I despise recursion
		return merge(mergeSort(left, arrayMiddle), arrayMiddle, mergeSort(right, arrayLength - arrayMiddle), arrayLength - arrayMiddle);
	}

}