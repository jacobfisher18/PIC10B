/*
 Jacob Fisher
 6/4/16
 Implements the compute_average_height(n) function to find the average height of a tree with n nodes
 */

#ifndef hw8_h
#define hw8_h

#include "bst.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

/*
 Salazar's vector shuffling algorithm
 Shuffles a vector with n entries.
 The algorithm:
 - For every index from 1 to n
 Generate random index r between 1 and n
	Exchange elements v[i] and v[r].
 */
void shuffleVector( vector<int>& v ){
    for ( int i=0 ; i < v.size() ; i++ ){
        int j = rand() % v.size() ; // <-- New random position
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

/* Computes the average height of a BST with n nodes */
double compute_average_height(int n) {
    
    const int MAX_NUM_TREES = 1000;
    
    srand( (int)time(0) );
    
    vector< BSTree<int> > trees;
    
    double totalHeight = 0; //double so that the average is a double
    int numTrees = 0; //will be incremented every time we add a tree
    
    for (int i = 0; i < MAX_NUM_TREES ; i++) {
        
        vector<int> v(n);
        
        //fill v with ints from 1 to n
        for (int j = 0; j < v.size(); j++)
            v[j] = j+1;
        
        //shuffle v
        shuffleVector(v);
        
        //Fill a BST with the values in v
        BSTree<int> tree;
        for (int j = 0; j < v.size(); j++ ){
            tree.insert(v[j]);
        }
        
        bool treeIsUnique = true;
        
        for (int j = 0; j < trees.size(); j++) {
            if (trees[j] == tree) {
                treeIsUnique = false;
            }
        }
        
        if (treeIsUnique) {
            trees.push_back(tree);
            totalHeight += tree.height();
            numTrees ++;
        }
    }
    
    return totalHeight / numTrees;
}

#endif
