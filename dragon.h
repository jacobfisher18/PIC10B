/*************************************************
 Jacob Fisher
 5/4/16
 
 A recursive function that calculates a dragon sequence
 *************************************************/

#ifndef dragon_hpp
#define dragon_hpp

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void generate_dragon_sequence(vector<bool> &v, int n, ostream& out) {
    
    //stopping condition and first case, start with a 1
    if (n == 1) {
        v.push_back(true);
        out << true << endl;
    }
    
    else {
        
        generate_dragon_sequence(v, n-1, out); //recursive, fill the segment of n-1 first
        
        v.push_back(true); //add a 1 at the end
        out << true << endl;
        
        //add the opposite of all the elements of v, backwards (excluding the 1 just placed at the end)
        for (int i = v.size()-2; i >=0; i--) {
            v.push_back(!v[i]);
            out << !v[i] << endl;
        }
    }
}

#endif