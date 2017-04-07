/*************************************************************
 hw3.cpp
 Jacob Fisher
 4/24/2016
 
 Program that repeatedly performs linear searches on a vector
 and computes the average number of comparisons needed to find
 an element.
 
 Running Time: T = O(N)
 *************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

const int numSearches = 1000; //number of times we search for a random element in each vector

//fisher-yeates shuffle, randomizes the order of a vector with no bias
template<typename T>
void scramble(std::vector<T>& v) {
    int j;
    T temp;
    for (int i = v.size() - 1; i > 0; i--) {
        j = rand() % (i+1);
        temp = v[j];
        v[j] = v[i];
        v[i] = temp;
    }
}

int main() {
    
    srand((int)time(0)); //sets the seed for random numbers
    
    int N;
    std::cout << "Please enter a number N" << std::endl;
    std::cin >> N;
    
    std::vector<int> omega[100]; //omega is a 100-length array that will hold int vectors
    
    double allAverages[100]; //array that holds all the average number of comparisons for all 100 int vectors
    
    //creates 100 vectors of random sizes between 1 and N, and fills each with values 1 through their size
    for (int i = 0; i < 100; i++) {
        int vectorSize = rand() % N + 1;
        for (int j = 0; j < vectorSize; j++) {
            omega[i].push_back(j + 1);
        }
        
        scramble(omega[i]); //randomizes the order of each of the vectors
    }
    
    
    for (int i = 0; i < 100; i++) {
        
        double totalComparisons = 0;
        double avgComparisons = 0;
        
        for (int j = 0; j < numSearches; j++) {
            
            int target = omega[i][rand() % omega[i].size()]; //target is set to a random element within the vector
            int index = 0; //the index of the target
            
            //searches the vector for the target and sets the index
            for (int k = 0; k < omega[i].size(); k++) {
                if (target == omega[i][k]) {
                    index = k;
                }
            }
            
            index++; //because indices start at 0, and we want to tell what order in the vector they are
            
            totalComparisons += index;
            avgComparisons = totalComparisons / (j+1);
        }
        
        allAverages[i] = avgComparisons;
        
    }
    
    std::ofstream fout;
    
    fout.open("data.txt");
    
    for (int i = 0; i < 100; i++) {
        fout << omega[i].size() << " " << allAverages[i] << std::endl;
    }
    
    fout.close();
    
    return 0;
}