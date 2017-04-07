/*
 Implementation of different sorting algorithms
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void printVector(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

//swap the values of two indices in an int vector
void swap(vector<int> &v, int i1, int i2) {
    int temp = v[i1];
    v[i1] = v[i2];
    v[i2] = temp;
}

void SelectionSort(vector<int>& v) {
    int firstUnsortedIndex = 0; //the vector is sorted up until this index
    while (firstUnsortedIndex != v.size()) {
        int minValue = v[firstUnsortedIndex];
        int minIndex = firstUnsortedIndex;
        for (int i = firstUnsortedIndex; i < v.size(); i++) {
            if (v[i] < minValue) {
                minValue = v[i];
                minIndex = i;
            }
        }
        swap(v, firstUnsortedIndex, minIndex);
        firstUnsortedIndex++;
    }
}

//v is the vector to be sorted, start is the first index in the portion of the vector to be sorted, and end is the last
void quickSort(vector<int>& v, int start, int end) {
    
    if (start < 0 || end > v.size()-1)
        return;
    
    //set the pivot to the first element in the subvector that we're sorting
    int pivot = v[start];
    
    vector<int> copy;
    
    //move all smaller values to the left of the pivot
    for (int i = start; i <= end; i++) {
        if (v[i] < pivot)
            copy.push_back(v[i]);
    }
    
    //move the pivot to where it is
    int pivotIndex = copy.size();
    copy.push_back(pivot);
    
    //move al bigger values to the right of the pivot
    for (int i = start; i <= end; i++) {
        if (v[i] >= pivot)
            copy.push_back(v[i]);
    }
    
    v = copy;
    
    //quickSort the subvector to the left of the pivot
    quickSort(v, start, pivotIndex-1);
    
    //quickSort the subvector to the right of the pivot
    quickSort(v, pivotIndex+1, end);
    
}

int main() {
    srand( (int)time(0) );
    
    vector<int> v;
    
    for (int i = 0; i < 10; i++) {
        v.push_back(rand() % 100 + 1);
    }
    
    cout << "Original Vector" << std::endl;
    printVector(v);
    
    quickSort(v, 0, v.size()-1);
    
    cout << "Sorted Vector" << std::endl;
    printVector(v);
    
    return 0;
}