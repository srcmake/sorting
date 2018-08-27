// Copyright srcmake.com 2018.
// C++ Sorting Algorithm Examples
// C++ Selection Sort, C++ Insertion Sort, C++ Merge Sort, C++ Quick Sort
// Official webpage for this tutorial: https://www.srcmake.com/home/sorting

/* Compile with:
g++ -std=c++14 main.cpp -o run
./run
*/

/* Note: We're passing our input vector to the 
algorithm function in a way that it'll be copied. 
In real life, you'd pass the vector by reference. */

#include <iostream>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////
////// PRINT A VECTOR //////
// Print a vector to stdout.
void PrintVector(vector<int> &a, string sortname)
	{
	cout << "Printing " << sortname << ": ";
	// Add a tab to make it look more presentable.
	if(sortname != "Selection sort" && sortname != "Insertion sort") { cout << "\t "; }
	for(int i = 0; i < a.size(); i++)
		{
		cout << a[i] << " ";
		}
	cout << endl;
	}
/////////////////////////////////////////////////////

	
//////////////////////////////////////////////////////
////// SELECTION SORT //////
// Running time: O(N^2). Space Required: O(1) Stable: No.
void SelectionSort(vector<int> a)
	{
	// Go through each element of the vector.
	for(int i = 0; i < a.size(); i++)
		{
		int currNum = a[i];
		int currIndex = i;
		
		// Search for the minimum element in the rest of the array.
		int minNum = a[i]; // Default it to the current element being min.
		int minIndex = i; 
		
		for(int j = i+1; j < a.size(); j++) // Every element after the current.
			{
			int num = a[j];
			int index = j;
			
			// If this element is smaller than the minimum so far, update the min variable.
			if(num < minNum)
				{
				minNum = num;
				minIndex = index;
				}
			}
		
		// We found the minimum number. Perform the swap.
		// (It's fine if the current element is the minimum.)
		int temp = currNum;
		a[currIndex] = minNum;
		a[minIndex] = temp;
		}
		
	// Output the sorted vector.
	PrintVector(a, "Selection sort");
	}
/////////////////////////////////////////////////////


//////////////////////////////////////////////////////
////// INSERTION SORT //////
// Running time: O(N^2). Space Required: O(1). Stable: Yes.
void InsertionSort(vector<int> a)
	{
	// Go through each element of the array (we don't need to check the first).
	for(int i = 1; i < a.size(); i++)
		{
		int currNum = a[i];
		int currIndex = i;
		
		// If the current element is smaller than the element to it's left (and a left element exists)...
		while(currNum < a[currIndex-1] && currIndex > 0)
			{
			int leftIndex = currIndex-1;
			int leftNum = a[leftIndex];
			
			// Swap the current number and it's left number.
			a[leftIndex] = currNum;
			a[currIndex] = leftNum;
			
			// Update the currIndex for the next iteration of this while loop.
			currIndex = leftIndex;
			}
		}
		
	// Output the sorted vector.
	PrintVector(a, "Insertion sort");
	}
/////////////////////////////////////////////////////


//////////////////////////////////////////////////////
////// MERGE SORT //////
// Running time: O(NlogN). Space Required: O(N) Stable: Yes.
// Help from: https://www.geeksforgeeks.org/merge-sort/
void Merge(vector<int> &a, int startIndex, int middleIndex, int endIndex)
	{
	// Size of the two subarrays.
	int n1 = middleIndex - startIndex + 1;
	int n2 = endIndex - middleIndex; 
	
	// Create temporary vectors.
	vector<int> L(n1);
	vector<int> R(n2);
	
	// Copy the data in a to our temp vectors.
	for(int i = 0; i < n1; i++)
		{ 
		L[i] = a[startIndex + i]; 
		}
	for(int i = 0; i < n2; i++)
		{ 
		R[i] = a[middleIndex + 1 + i]; 
		}
	
	// Merge the temp vectors back into a.
	int leftIndex = 0;			// Initial index of the first subarray.
	int rightIndex = 0;			// Initial index of the second subarray.
	int mergedIndex = startIndex; // Initial index of the merged array.
	
	// Selectively choose the smallest element from the subarrays to put into the merged array. 
	while(leftIndex < n1 && rightIndex < n2)
		{
		int leftNum = L[leftIndex];
		int rightNum = R[rightIndex];
		
		// The left number is smaller, so put it in the merged array.
		// And increment the index.
		if(leftNum <= rightNum)
			{
			a[mergedIndex] = leftNum;
			leftIndex++;
			}
		// The right number is smaller, so put it in the merged array.
		else
			{
			a[mergedIndex] = rightNum;
			rightIndex++;
			}
		mergedIndex++;
		}
	
	// Copy any remaining elements in the left and right subarrays, if there are any.
	while(leftIndex < n1)
		{
		a[mergedIndex] = L[leftIndex];
		leftIndex++;
		mergedIndex++;
		}
	while(rightIndex < n2)
		{
		a[mergedIndex] = R[rightIndex];
		rightIndex++;
		mergedIndex++;
		}
	}

void Divide(vector<int> &a, int startIndex, int endIndex)
	{
	// This (sub)array is bigger than 2 elements, so divide it.
	if(startIndex < endIndex) 
		{
		int middleIndex = (startIndex + endIndex)/2;
		
		// Recursively divide the two subarrays we can form from this.
		Divide(a, startIndex, middleIndex);
		Divide(a, middleIndex+1, endIndex);
		
		// Now merge these two subarrays together.
		Merge(a, startIndex, middleIndex, endIndex);
		}
	}

void MergeSort(vector<int> a)
	{
	// Divide needs to be called recursively.
	// We begin by dividing a from the first index to the last.
	Divide(a, 0, a.size()-1);	
		
	// Output the sorted vector.
	PrintVector(a, "Merge sort");
	}
/////////////////////////////////////////////////////


//////////////////////////////////////////////////////
////// QUICK SORT //////
// Running time: O(NlogN). Space Required: O(N) Stable: Yes.
int Partition(vector<int> &a, int startIndex, int endIndex)
	{
	// Choose our pivot as the last element in the array.
	int pivotNum = a[endIndex];
	int pivotIndex = endIndex;
	
	// The index of our "wall".
	// Left of the wall means smaller elements than the pivot.
	// Right of the wall means bigger elements than the pivot.
	int wallIndex = startIndex-1;
	
	// Go through each element in this subarray.
	for(int i = startIndex; i <= endIndex-1; i++)
		{
		int currNum = a[i];
		int currIndex = i;
		
		// If the current element is smaller than (or equal to) the pivot...
		if(currNum <= pivotNum)
			{
			// Increment our wallIndex. (Move our wall to the right.)
			wallIndex++;
			// The number at the wall.
			int wallNum = a[wallIndex];
			// Swap the current element and whatever is right of the wall (which is at the new wallIndex).
			a[wallIndex] = currNum;
			a[currIndex] = wallNum;
			}
		}
	
	// Finally, move our pivot number to the right of the wall (in between the subarrays).
	wallIndex++;
	int wallNum = a[wallIndex];
	a[wallIndex] = pivotNum;
	a[pivotIndex] = wallNum;
	
	// Return the index of the pivot (which is now the wallIndex.
	return wallIndex;
	}

void QDivide(vector<int> &a, int startIndex, int endIndex)
	{
	// If the subarray is bigger than one element in size...
	if(startIndex < endIndex)
		{
		// Partition the array.
		int pivotIndex = Partition(a, startIndex, endIndex);
		
		// Recursively divide and partition the two subarrays.
		QDivide(a, startIndex, pivotIndex-1);
		QDivide(a, pivotIndex+1, endIndex);
		}
	}

void QuickSort(vector<int> a)
	{
	// Recursively divide the vector. Start from the beginning and the end.
	QDivide(a, 0, a.size()-1);
	
	// Output the sorted vector.
	PrintVector(a, "Quick sort");
	}
/////////////////////////////////////////////////////

	
//////////////////////////////////////////////////////
////// MAIN //////
int main() 
    {
	cout << "Program started.\n";
	
	// Let's create an unsorted array (vector).
	vector<int> a = {3, 5, 1, 3, 4, 8, 1, 7, 11, 9, 2, 5, 6, 1};
	
	// Print our unsorted vector out.
	PrintVector(a, "Unsorted");
	
	// Call each of our sorting algorithms (function) on our vector.
	SelectionSort(a);
	InsertionSort(a);
	MergeSort(a);
	QuickSort(a);
	
	cout << "Program ended.\n";
    return 0;
    }
//////////////////////////////////////////////////////