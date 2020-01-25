#include <vector>
#include <math.h> // may need to use pow( )
using namespace std;

template <class Comparable>
void merge( vector<Comparable> &a, int first, int mid, int last, vector<Comparable> &tempArray ) {
  int first1 = first; int last1 = mid;         // the left array[first1..last1]
  int first2 = mid + 1; int last2 = last;     // the right array[first2..last2]

  int index = first1;
  for ( ; first1 <= last1 && first2 <= last2; ++index ) // choose a smaller
    tempArray[index] = ( a[first1] < a[first2] ) ? a[first1++] : a[first2++];
  
  for ( ; first1 <= last1; ++first1, ++index )      // exhaust the left array
    tempArray[index] = a[first1];

  for ( ; first2 <= last2; ++first2, ++index )      // exhaust the right array
    tempArray[index] = a[first2];

  for ( index = first; index <= last; ++index )  // write them back to original
    a[index] = tempArray[index];
}

template<class Comparable>
void mergeImproved(vector<Comparable> &a) {
	int size = a.size();
	vector<Comparable> b (size);  // this is only one temporary array.
	int left;
	int length;
	//Each time the size will be two times the previous (1 to 2 to 4, ...)
	for (length = 1; length < size; length *= 2) {
		// Combine sections of array a of size "length"
		for (left = 0; left < size - 1; left += (2 * length)) {
			//calculate the mid
			int middle = left + length - 1 < size - 1 ? left + length - 1 : size - 1;

			//calculate the minimum, size-1 once we hit the end of the vector
			int right = left + (2 * length) - 1 < size - 1 ? left + (2*length) - 1 : size - 1;

			//merge the two vectors
			merge(a, left, middle, right, b);
		}
	}
}

