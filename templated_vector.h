/* *************************************************
 Jacob Fisher
 4/30/16
 
 A custom templated vector class.
 ************************************************* */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

template <typename T>
class MyVector;

//Scalar Multiplication
template <typename T>
MyVector<T> operator*(int, MyVector<T>);
template <typename T>
MyVector<std::string> operator*(std::string s, MyVector<std::string>); //specialized for string and MyVector<string>

//Scalar Multiplication (Symmetric)
template <typename T>
MyVector<T> operator*(MyVector<T>, int);
template <typename T>
MyVector<std::string> operator*(MyVector<std::string>, std::string s); //specialized for string and MyVector<string>

//MyVector<string> Multiplication
template <typename T>
MyVector<std::string> operator*(MyVector<std::string> v1, MyVector<std::string> v2);

//Output Operator Overload
template <typename T>
std::ostream& operator<<( std::ostream& out, const MyVector<T>& v);
template <>
std::ostream& operator<<( std::ostream& out, const MyVector<std::string>& v); //specialized for MyVector<string>

// Relational operator overloading specialized for strings
bool operator<=( const MyVector<std::string>& v1, const MyVector<std::string>& v2);
bool operator>=( const MyVector<std::string>& v1, const MyVector<std::string>& v2);
bool operator<( const MyVector<std::string>& v1, const MyVector<std::string>& v2);
bool operator>( const MyVector<std::string>& v1, const MyVector<std::string>& v2);
bool operator==( const MyVector<std::string>& v1, const MyVector<std::string>& v2);
bool operator!=( const MyVector<std::string>& v1, const MyVector<std::string>& v2);

template <typename T>
class MyVector {
public:
    
    // The Big 4
    MyVector(); // Default constructor
    ~MyVector(); // Destructor
    MyVector(const MyVector<T>& b); // Copy Constructor
    MyVector& operator=(const MyVector<T>& b); // Assignment operator
    
    // Member functions
    void push_back(T newValue);
    int size() const;
    
    // operator[]
    T& operator[](int n); // getter for an element at position n
    T operator[](int n) const; // setter for an element at position n
    
    // Operator Overloading
    MyVector operator+(const MyVector<T>& b) const;
    MyVector& operator+=(const MyVector<T>& b);
    double operator*(const MyVector<T>& b) const ; // to compute dot products
    
    // Relational operator overloading
    bool operator<=( const MyVector<T>& b) const;
    bool operator>=( const MyVector<T>& b) const;
    bool operator<( const MyVector<T>& b) const;
    bool operator>( const MyVector<T>& b) const;
    bool operator==( const MyVector<T>& b) const;
    bool operator!=( const MyVector<T>& b) const;
    
private:
    void reserve(int newCapacity);
    int compare(const MyVector<T>& b) const;
    
    static const int INITIAL_SIZE = 10;
    int currentCapacity;
    int numItems;
    T* theData;
};

// Default constructor
template <typename T>
MyVector<T>::MyVector() {
    std::cout << "Standard constructor called..." << std::endl;
    currentCapacity = INITIAL_SIZE;
    numItems = 0;
    theData = new T[INITIAL_SIZE];
}

// Destructor
template <typename T>
MyVector<T>::~MyVector() {
    std::cout << "Destructor called. Relasing memory..." << std::endl;
    delete[] theData;
    theData = 0;
}

// Copy constructor
template <typename T>
MyVector<T>::MyVector(const MyVector<T>& b) {
    std::cout << "Copy constructor called..." << std::endl;
    
    // shallow copy non-pointers
    currentCapacity = b.currentCapacity;
    numItems = b.numItems;
    
    //deep copy pointers (if neccesary)
    if (b.theData != NULL) {
        theData = new T[b.currentCapacity]; //alocate memory
        
        for (int i=0 ;i < b.numItems; i++)
            theData[i] = b.theData[i];
    }
    
    else
        theData = NULL;
    
}

// Assignment Operator
template <typename T>
MyVector<T>& MyVector<T>::operator=( const MyVector<T>& b ){
    std::cout << "operator= called..." << std::endl;
    
    // check for self-assignment
    if (this == &b)
        return *this;
    
    // release memory in current object
    delete[] this->theData;
    
    // shallow copy non-pointers
    currentCapacity = b.currentCapacity;
    numItems = b.numItems;
    
    // deep copy pointers (if necessary)
    if ( b.theData != NULL) {
        theData = new T[b.currentCapacity];
        
        for ( int i=0 ; i < b.numItems ; i++ )
            theData[i] = b.theData[i];
    }
    
    else
        theData = NULL;
    
    return *this;
}

// Size member function, returns the size of the MyVector
template <typename T>
int MyVector<T>::size() const {
    return numItems;
}

//add an item to the end of the MyVector
template <typename T>
void MyVector<T>::push_back(T newValue) {
    // make sure there is enough space
    if (numItems == currentCapacity)
        reserve(currentCapacity + 1);
    
    theData[numItems] = newValue;
    numItems++;
    
    return;
}

//reserve some more heap space for the MyVector
template <typename T>
void MyVector<T>::reserve(int newCapacity){
    if (newCapacity > currentCapacity) {
        
        // Make sure we at least double the current capacity
        if (newCapacity > 2*currentCapacity)
            currentCapacity = newCapacity;
        else
            currentCapacity *= 2;
        
        // request more space in the heap
        T* newData = new T[currentCapacity];
        
        //copy the data
        for (int i=0 ; i < numItems ; i++)
            newData[i] = theData[i];
        
        // release memory from the old location
        delete[] theData;
        
        // update memory address
        theData = newData;
    }
    
    return;
}

// operator[] as a setter
template <typename T>
T& MyVector<T>::operator[](int n){
    
    // if n is not a valid index do something
    
    return *(theData + n); // same as theData[n]
}

// operator[] as a getter
template <typename T>
T MyVector<T>::operator[](int n) const {
    
    // if n is not a valid index do something
    
    return *(theData + n); //same as theData[n]
}

// more operator overloading
template <typename T>
MyVector<T> MyVector<T>::operator+(const MyVector<T>& b) const {
    MyVector c(b); //use the copy constructor to make a deep copy of b called c
    
    //set every element of c to be the sum of the corresponding element of this and b
    for (int i=0; i<c.size(); i++)
        c[i] = theData[i] + b[i];
    
    return c;
}

// Implementaion based on operator= to avoid repetition of code
template <typename T>
MyVector<T>& MyVector<T>::operator+=( const MyVector<T>& b ){
    *this = *this + b; //uses the assignment operator and operator+
    
    return *this;
}

// This is a product between two vectors and is a member function.
// Compare to nonmembers:
// MyVector operator* ( int, const MyVector& b );
// MyVector operator* ( const MyVector& b , int );
template <typename T>
double MyVector<T>::operator*( const MyVector<T>& b) const {
    // Assume *this and b have the same size.
    double sum = 0;
    for (int i=0 ; i<b.size() ; i++)
        sum += theData[i] * b[i];
    
    return sum;
}



/**************************************************
 Relational Operators
 
 To avoid repetition, the operators <, <=, > and >=
 are based on a private member function that
 returns an integer.
 The idea is to use the following equivalent
 statements:
 
 x > y  if and only if  (x - y) > 0
 x >= y if and only if  (x - y) >= 0
 x < y  if and only if  (x - y) < 0
 x <= y if and only if  (x - y) <= 0
 
 Implement a private member function 'compare' that
 returns:
 - a positive integer if implicit parameter is bigger than b
 - a nonnegative integer if implicit parameter is bigger or equal to b
 - a negatove integer if implicit parameter is less than b
 - a nonpositive integer if implicit parameter is less or equal to b
 ************************************************* */
template <typename T>
int MyVector<T>::compare( const MyVector<T>& b ) const {
    return std::sqrt( (*this) * (*this) - b * b ) ;
}

template <typename T>
bool MyVector<T>::operator>( const MyVector<T>& b ) const {
    return compare(b) > 0 ;
}

template <typename T>
bool MyVector<T>::operator>=( const MyVector<T>& b ) const {
    return compare(b) >= 0 ;
}

template <typename T>
bool MyVector<T>::operator<( const MyVector<T>& b ) const {
    return compare(b) < 0;
}

template <typename T>
bool MyVector<T>::operator<=( const MyVector<T>& b ) const {
    return compare(b) <= 0;
}

template <typename T>
bool MyVector<T>::operator==( const MyVector<T>& b ) const {
    // False if different sizes
    if( size() != b.size() )
        return false;
    else{
        // False if at least one entry does not match
        for (int i=0 ; i<size() ; i++){
            if ( theData[i] != b[i] )
                return false;
        }
        // True if all entries match
        return true;
    }
}

template <typename T>
bool MyVector<T>::operator!=( const MyVector<T>& b ) const {
    return !( *this == b );
}


/**************************************************
 NON MEMBER OPERATORS
 ************************************************* */
template <typename T>
MyVector<T> operator*(int a, MyVector<T> v) {
    for ( int i=0 ; i < v.size() ; i++ ){
        v[i] = a * v[i];  // Shouldn't we treat value parameters as constants??? See (*) below.
    }
    return v; // v is a local copy of the vector
}

template <typename T>
MyVector<T> operator*( MyVector<T> v , int a){
    return a * v;
}

// Output operator <<
template <typename T>
std::ostream& operator<<( std::ostream& out , const MyVector<T>& v ){
    for (int i=0; i < v.size() - 1; i++)
        out << v[i] << ", ";
    out << v[v.size()-1];
    out << std::endl;
    
    return out;
}

// Output operator << for strings
template <>
std::ostream& operator<<( std::ostream& out , const MyVector<std::string>& v ){
    for (int i=0; i < v.size(); i++)
        out << v[i] << " ";
    out << std::endl;
    
    return out;
}

#endif