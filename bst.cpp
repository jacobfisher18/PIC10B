/******************************
 Jacob Fisher
 A program that implements a binary search tree of ints
******************************/

#include <iostream>
#include <iomanip>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
    
    Node(int theData) {
        data = theData;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    BST();
    void insert(int value);
    void print();
    
    int find(int target); //search for a target within the BST
    Node* get_parent(Node* childNode); //given a pointer to a node, return a pointer to its parent
    void pre_order(Node* root); //pre-oder traversal used to print to the console
    void post_order(Node* root); //post-oder traversal used to print to the console
    void in_order(Node* root); //in-oder traversal used to print to the console
    
    Node* get_root();
private:
    Node *root;
    
    void insertHelper(Node* rootNode, Node* newNode);
    void printHelper(Node *rootNode);
};

BST::BST() {
    root = NULL;
}

void BST::insertHelper(Node* rootNode, Node* newNode) {
    
    if (newNode->data < rootNode->data) {
        if (rootNode->left == NULL)
            rootNode->left = newNode;
        else
            insertHelper(rootNode->left, newNode);
    }
    
    if (newNode->data > rootNode->data) {
        if (rootNode->right == NULL)
            rootNode->right = newNode;
        else
            insertHelper(rootNode->right, newNode);
    }
}

void BST::insert(int value) {
    Node *newNode = new Node(value);
    if (root != NULL) {
        insertHelper(root, newNode);
    }
    
    else {
        root = newNode;
    }
}

void BST::printHelper(Node *rootNode) {
    if (rootNode != NULL) {
        cout << "Value: " << rootNode->data;
        if (rootNode->left != NULL)
            cout << " Left: " << rootNode->left->data;
        if (rootNode->right != NULL)
            cout << " Right: " << rootNode->right->data;
        cout << endl;
    }
    
    if (rootNode->left != NULL)
        printHelper(rootNode->left);
    
    if (rootNode->right != NULL)
        printHelper(rootNode->right);
}

void BST::print() {
    printHelper(root);
}

void BST::pre_order(Node* root) {
    if (root == NULL)
        return;
    cout << root->data << " ";
    pre_order(root->left);
    pre_order(root->right);
}

void BST::post_order(Node* root) {
    if (root == NULL)
        return;
    post_order(root->left);
    post_order(root->right);
    cout << root->data << " ";
}

void BST::in_order(Node* root) {
    if (root == NULL)
        return;
    in_order(root->left);
    cout << root->data << " ";
    in_order(root->right);
}

Node* BST::get_root() {
    return root;
}

int main() {
    
    BST myTree;
    
    myTree.insert(8);
    myTree.insert(3);
    myTree.insert(10);
    myTree.insert(1);
    myTree.insert(6);
    myTree.insert(14);
    myTree.insert(4);
    myTree.insert(7);
    myTree.insert(13);
    
    cout << "Pre oder: ";
    myTree.pre_order(myTree.get_root());
    cout << endl;
    
    cout << "Post oder: ";
    myTree.post_order(myTree.get_root());
    cout << endl;
    
    cout << "In oder: ";
    myTree.in_order(myTree.get_root());
    cout << endl;
    
    return 0;
}