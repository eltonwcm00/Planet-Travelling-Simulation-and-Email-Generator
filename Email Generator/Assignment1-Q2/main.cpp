// Question 2 - AVL Tree

// C++ program for AVL Tree
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
// #include "BinarySearchTree.cpp"
using namespace std;

const int D_S = 100;

class AVLNode
{
public:
    int key;
    AVLNode *left;
    AVLNode *right;
    int depth;
};

//get max of two integers
int max(int a, int b){
    return (a > b)? a : b;
}

//function to get height of the tree
int depth(AVLNode *n)
{
    if (n == NULL)
        return 0;
    return n->depth;
}
// allocate a new node with key passed
AVLNode* newNode(int key)
{
    AVLNode* node = new AVLNode();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->depth = 1; // new node added as leaf
    return(node);
}
// right rotate the sub tree rooted with y
AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->depth = max(depth(y->left),
                   depth(y->right)) + 1;
    x->depth = max(depth(x->left),
                   depth(x->right)) + 1;

    // Return new root
    return x;
}

// left rotate the sub tree rooted with x
AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;
    // Update heights
    x->depth = max(depth(x->left),
                   depth(x->right)) + 1;
    y->depth = max(depth(y->left),
                   depth(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return depth(N->left) -
           depth(N->right);
}
//insertion operation for node in AVL tree
AVLNode* insert(AVLNode* node, int key)  {
    //normal BST rotation
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys not allowed
        return node;

    //update height of ancestor node
    node->depth = 1 + max(depth(node->left),  depth(node->right));

    int balance = getBalance(node);        //get balance factor

    // rotate if unbalanced

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// find the node with minimum value
AVLNode * minValueNode(AVLNode* node)
{
    AVLNode* current = node;

    // find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// delete a node from AVL tree with the given key
AVLNode* deleteNode(AVLNode* root, int key)
{
    if (root == NULL)
        return root;

    //perform BST delete
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            AVLNode *temp = root->left ?
                            root->left :
                            root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp;
            free(temp);
        }
        else
        {
            AVLNode* temp = minValueNode(root->right);

            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    if (root == NULL)
        return root;

    // update depth
    root->depth = 1 + max(depth(root->left),
                          depth(root->right));

    // get balance factor
    int balance = getBalance(root);

    //rotate the tree if unbalanced

    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&  getBalance(root->left) < 0)  {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 &&  getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)   {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
// prints inOrder traversal of the AVL tree
void inOrder(AVLNode *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}
// convert string in dataset to ASCII
int convertToASCII(string letter) {
    int newVar = 0;

    for (int i = 0; i < letter.length(); i++) {
        char x = letter.at(i);
        newVar = newVar + x;
    }
    return newVar;
}
// users input their search data and it runs through the dataset to check
int searchData() {

    string choice;
    int newVarUser;

    cout << "\nEnter the email that you would like to search for : ";
    getline(cin, choice);
    cout << "\n";

    newVarUser = convertToASCII(choice);

    return newVarUser;
}

// main code
int main() {

    AVLNode *root = NULL;

//  AVLNode root;

    int i;
    bool check;
    string* dataset = new string[D_S];
    int newVarUser;
    int* newVar = new int[D_S];

    ifstream infile;

    infile.open ("setB.txt");

    if(infile.is_open()) {

        auto startInsert = chrono::system_clock::now();

        for(i = 0; i < D_S; i++) {

            getline(infile,dataset[i]); //infile >> dataset[i];
            newVar[i] = convertToASCII(dataset[i]); //convert string to ascii int from data set

            root = insert(root, newVar[i]);

            cout << "\n\nInorder traversal for the AVL tree is: \n";
            inOrder(root);
        }

        auto endInsert = chrono::system_clock::now();
        chrono::duration<double> duration = endInsert - startInsert;
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(5);
        cout << "\n\nDuration taken for inserting : " << duration.count() << "s\n";
    }

    for(int x=0; x<10; x++) {

        newVarUser = searchData();

        auto startSearch = chrono::system_clock::now();

        for (i = 0; i < D_S; ++i) {
            if (newVarUser == newVar[i]) {
                check = true;
                break;
            } else {
                check = false;
            }
        }

        if (check) {
            cout << "Target is found" << endl;
        } else {
            cout << "Target is not found" << endl;
        }

        auto endSearch = chrono::system_clock::now();
        chrono::duration<double> duration = endSearch - startSearch;
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(5);
        cout << "\nDuration taken for searching : " << duration.count() << "s\n";

    }

    infile.close();
}

