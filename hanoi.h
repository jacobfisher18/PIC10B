/*************************************
 Jacob Fisher
 5/17/16
 An implementation of a stack using a linked list, used to solve the Tower of Hanoi
 ************************************/

#ifndef hanoi_hpp
#define hanoi_hpp

#include <string>
#include <iostream>

template <typename T>
class Node;

template <typename T>
class Stack;

//Output operator overload for Stacks
template <class T>
std::ostream& operator<<(std::ostream& out, const Stack<T>& s);

//The Node Class, which stores a piece of data and a pointer to the next piece of data
template <class T>
class Node {
public:
    Node(const T& newData); //Node constructor
    
    friend class Stack<T>;
    
private:
    T data; //the data stored in this node
    Node* next; //a link to the next node (in our stack, we would visualize this as the node below the current one)
};

//Node Constructor
template<class T>
Node<T>::Node(const T& newData){
    data = newData;
    next = NULL;
}

template <class T>
class Stack {
public:
    Stack(std::string myName); //constructor with name parameter
    Stack(std::string myName, int DEPTH); //constructor with depth parameter, specialized for ints only
    
    //Big 4
    Stack(); //default constructor
    ~Stack(); //destructor
    Stack(const Stack<T>& b); //copy constructor
    Stack<T>& operator=(const Stack<T>& b); //assignment operator
    
    //modifiers
    void push(const T& newData);
    T pop();
    
    //accessors
    int size() const;
    std::string get_name() const;
    T get_top() const; //returns the data stored in the top node
    
    //A function used by the output<< operator to access private elements of Stack
    void output(std::ostream& out) const;
    
private:
    Node<T>* top; //a pointer to the node on top of the stack
    std::string name; //the name of the stack
    int count; //the number of elements in the stack
    
    void deep_copy(const Stack<T>& b); //to help with the copy constructor and assignment operator
};

/********************************************
 Constructors
********************************************/

//constructor with name parameter
template <class T>
Stack<T>::Stack(std::string myName) {
    top = NULL;
    name = myName;
    count = 0;
}

//constructor with depth parameter, specialized for ints only
template<>
Stack<int>::Stack(std::string myName, int DEPTH) {
    top = NULL;
    name = myName;
    count = 0;
    
    for (int i = 0 ; i < DEPTH ; i++)
        this->push(DEPTH - i);
}

/********************************************
 The Big Four
 ********************************************/

//default constructor
template <class T>
Stack<T>::Stack() {
    top = NULL;
    name = "unnamed_stack";
    count = 0;
}

//destructor
template <class T>
Stack<T>::~Stack() {
    while (top != NULL) {
        pop();
    }
}

//works by copying all the elements into a new Stack in reverse order, and then copying those elements back in reverse order
template <class T>
void Stack<T>::deep_copy(const Stack<T>& b) {
    top = NULL;
    
    //a stack that will contain all the elements stack b in reverse order
    Stack<T> reversed;
    
    Node<T> *curr = b.top;
    
    //fill reversed with all the elements in stack b, starting from the top
    while (curr != NULL) {
        reversed.push(curr->data);
        curr = curr->next;
    }
    
    curr = reversed.top;
    
    //copy all the elements of reversed into this, starting from the top
    while (curr != NULL) {
        push(curr->data);
        curr = curr->next;
    }
}

//copy constructor
template <class T>
Stack<T>::Stack(const Stack<T>& b) {
    deep_copy(b);
    name = b.name;
}

//assignment operator
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& b) {
    //check for self assignment
    if (this != &b) {
        (*this).~Stack(); //release memory of pointers
        deep_copy(b);
        name = b.name;
    }
    
    return *this;
}

/********************************************
 Modifiers
 ********************************************/

template <class T>
void Stack<T>::push(const T& newData) {
    
    Node<T>* newNode = new Node<T>(newData); //memory for a new node based on the parameter passed

    newNode->next = top;
    
    top = newNode;
    
    count++;
}

template <class T>
T Stack<T>::pop() {
    T oldTop = top->data; //store the contents of the node that will be deleted so as to return it at the end
    
    //if there is at least 1 element in the stack
    if (top != NULL) {
        
        //if there's exactly 1 element in the stack
        if (top->next == NULL) {
            delete top;
            top = NULL;
            count--;
        }
        
        //there are at least 2 elements in the stack
        else {
            Node<T>* newTop = top->next;
            delete top;
            top = newTop;
            count--;
        }
    }
    
    return oldTop;
}

/********************************************
 Accessors
 ********************************************/

template <class T>
int Stack<T>::size() const {
    return count;
}

template <class T>
std::string Stack<T>::get_name() const {
    return name;
}

template <class T>
T Stack<T>::get_top() const {
    return top->data;
}

/********************************************
 Other Functions
 ********************************************/

//helper function to output the stack (from bottom to top)
//works by creating another stack that is the reverse of the original, and ouputting that one top to bottom
template <class T>
void Stack<T>::output(std::ostream& out) const {
    
    //a stack that will contain all the elements of this stack in reverse order
    Stack<T> reversed;
    
    Node<T> *curr = top;
    
    //fill reversed with all the elements in this stack, starting from the top
    while (curr != NULL) {
        reversed.push(curr->data);
        curr = curr->next;
    }
    
    curr = reversed.top;
    
    //output all the elements of reversed, starting from the top
    while (curr != NULL) {
        out << curr->data << " ";
        curr = curr->next;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out , const Stack<T>& s){
    
    out << s.get_name() << ": ";
    
    s.output(out);
    
    out << "\n";
    
    return out;
}

//moves the the top of one stack to the top of another
void movePiece(Stack<int> &start, Stack<int> &end) {
    end.push(start.get_top());
    start.pop();
}

void hanoi(Stack<int> &source, Stack<int> &aux, Stack<int> &target, int disks, std::ostream& out) {
    if (disks > 1) {
        hanoi(source, target, aux, disks-1, out);
        
        out << "Moving " << source.get_top() << " from " << source.get_name() << " to " << target.get_name() << "." << std::endl;
        movePiece(source, target);
        out << source << aux << target << std::endl;
        
        hanoi(aux, source, target, disks-1, out);
    }
    
    else {
        out << "Moving " << source.get_top() << " from " << source.get_name() << " to " << target.get_name() << "." << std::endl;
        movePiece(source, target);
        out << source << aux << target << std::endl;
    }
}

#endif