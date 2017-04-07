#include "hw1.h"

//function prototypes
int max(int &A, int &B);
double max(double &A, double &B);

//given the initial vector, the Student constructor should assign and calculate all its private variables
Student::Student(std::vector<int> v) {
    
    //fill list homeworks with the first 8 integers of vector v
    for (int i = 0; i < 8; i ++) {
        homeworks.push_back(v[i]);
    }
    
    //set midterm1, midterm2, and final to the last three values of vector v
    midterm1 = v[8];
    midterm2 = v[9];
    final = v[10];
    
    //iterates through the homeworks list, sets the homeworkAvg variable to the average of this list
    std::list<int>::iterator i;
    for (i = homeworks.begin(); i != homeworks.end(); ++i) {
        homeworkAvg += *i * 5.0; //multiply by 5 because scores are out of 20
    }
    homeworkAvg /= 8;
    
    highestMidterm = max(midterm1, midterm2);
    
    finalGradeA = (homeworkAvg * 0.25) + (midterm1 * 0.2) + (midterm2 * 0.2) + (final * 0.35);
    finalGradeB = (homeworkAvg * 0.25) + (highestMidterm * 0.3) + (final * 0.44);
    
    overallScore = max(finalGradeA, finalGradeB);
}

void Student::print(std::ostream &out) const {
    out << "Score A: " << finalGradeA  << "\nScore B: " << finalGradeB << "\nOverall Score: " << std::fixed << std::setprecision(2) << overallScore << "%" << std::endl;
}

//function that returns the maximum of two integers
int max(int &A, int &B) {
    if (A > B)
        return A;
    else
        return B;
}

//function that returns the maximum of two doubles
double max(double &A, double &B) {
    if (A > B)
        return A;
    else
        return B;
}

void compute_overall_score(std::string inputFile, std::string outputFile) {
    
    std::vector<int> v; //holds all the scores on every assignment
    
    //fstream objects
    std::ifstream fin;
    std::ofstream fout;
    
    fin.open(inputFile.c_str());
    
    //read in all the numbers in the input file to vector v
    int inputNum;
    while (fin >> inputNum) {
        v.push_back(inputNum);
    }
    
    fin.close();
    
    //note: the Student constructor calculates all of the Student's private variables
    Student myStudent(v);
    
    myStudent.print(std::cout);
    
    fout.open(outputFile.c_str());
    myStudent.print(fout);
    fout.close();
}