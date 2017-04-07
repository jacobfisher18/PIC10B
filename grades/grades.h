/*
 Jacob Fisher
 4/7/16
 Implements a program that helps students compute their grade in a class
 Demonstrates review of separate compilation, custom classes, passing by reference, iterators, vectors, and file i/o
*/

#ifndef HW1_H
#define HW1_H

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <iostream>
#include <iomanip>

//function prototypes
void compute_overall_score(std::string, std::string);

//the student class is initialized with a vector of 11 scores, and it categorizes those scores and computes the final scores
class Student {
public:
    Student(std::vector<int> v);
    void print(std::ostream &out) const; //outputs the final scores to either the console or a file (specified by the parameter)
private:
    std::list<int> homeworks; //holds all homework scores
    int midterm1;
    int midterm2;
    int final;
    
    double homeworkAvg; //average of all the homework scores
    int highestMidterm;
    
    double finalGradeA;
    double finalGradeB;
    double overallScore; //the score yielded by the better of the two grading schemes
};

#endif