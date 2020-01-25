#include <iostream>
#include <vector>
#include <stdlib.h>
#include "mergeImproved.cpp"
#include "mergesort.cpp"
#include "quicksort.cpp"
#include <sys/time.h>
#include <fstream>
// array initialization with random numbers
void initArray(vector<int> &array, int randMax) {
	int size = array.size();

	for (int i = 0; i < size;) {
		int tmp = (randMax == -1) ? rand() : rand() % randMax;
		bool hit = false;
		for (int j = 0; j < i; j++) {
			if (array[j] == tmp) {
				hit = true;
				break;
			}
		}
		if (hit)
			continue;
		array[i] = tmp;
		i++;
	}
}

// array printing
void printArray(vector<int> &array, char arrayName[]) {
	int size = array.size();

	for (int i = 0; i < size; i++)
		cout << arrayName << "[" << i << "] = " << array[i] << endl;
}

//calculate elapsed time
int elapsed(timeval &startTime, timeval &endTime) {
	return (endTime.tv_sec - startTime.tv_sec) * 1000000
			+ (endTime.tv_usec - startTime.tv_usec);
}

int main(int argc, char* argv[]) {
	// verify arguments
	if (argc != 2) {
		cerr << "usage: quicksort size" << endl;
		return -1;
	}

	// verify an array size
	int size = atoi(argv[1]);
	if (size <= 0) {
		cerr << "array size must be positive" << endl;
		return -1;
	}

	//check if the mergeImproved work correctly
	ofstream out("size30.txt"); //create a size30.txt
	auto *coutbuf = cout.rdbuf(); //redirect cout to print the data into the text file
	cout.rdbuf(out.rdbuf());
	// array generation
	srand(1);
	vector<int> items(size);
	initArray(items, size);
	cout << "initial:" << endl;
	printArray(items, "items");

	// mergesort
	mergeImproved(items);
	cout << "sorted:" << endl;
	printArray(items, "items");
	cout.rdbuf(coutbuf); //redirect cout to print to the console
	out.close();

	ofstream outfile;
	outfile.open("compare.txt"); //Create an output file with "compare.txt" filename.
	outfile << "size \t quicksort \t mergesort \t mergeImproved \n";
	for (int i = 20; i <= 1000; i += 20) {
		outfile << i << "\t";
		srand(time(0));
		vector<int> item(i, 0);
		initArray(item, i);
		vector<int> items1(item);
		vector<int> items2(item);
		vector<int> items3(item);
		timeval startTime, endTime;
		///----------------quicksort------------------
		gettimeofday(&startTime, 0);
		quicksort(items1);
		gettimeofday(&endTime, 0);
		int e_time = elapsed(startTime, endTime);
		outfile << e_time << "\t";

		//-------------------mergesort------------
		gettimeofday(&startTime, 0);
		mergesort(items2);
		gettimeofday(&endTime, 0);
		e_time = elapsed(startTime, endTime);
		outfile << e_time << "\t";

		//-------------------mergeImproved------------
		gettimeofday(&startTime, 0);
		mergeImproved(items3);
		gettimeofday(&endTime, 0);
		e_time = elapsed(startTime, endTime);
		outfile << e_time << "\n";
		//-----------------------
	}

	outfile.close();

	return 0;
}
