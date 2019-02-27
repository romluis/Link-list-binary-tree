#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include "node.h"
#include "parser.h"

using namespace std;

enum ORDER {IN_ORDER, POST_ORDER, PRE_ORDER};

template<typename T>
class binaryTree
{
   friend class Parser;
    public:
        // ____________________________________________________________CONSTRUCTORS / DESTRUCTOR
        binaryTree();                                               // Defualt constructor
        binaryTree(T d, int c = 1);                                 // Single data with count Tree constr
        ~binaryTree();                                              // Destructor
        binaryTree(const binaryTree<T> &other);                     // Copy constructor
        binaryTree<T>& operator=(const binaryTree<T> &other);       // Assignment operator

        // ____________________________________________________________FUNCTIONS
        void insert(T d, int c = 1);                                // Insert data of count 1 to list
        bool remove(T d);                                           // Remove data from tree
        int find(T d);                                              // Find data in tree
        ORDER getTraversal();                                       // Return traversal
        void setTraversal(ORDER traversal);                         // Set tree traversal
        int depth();                                                // Returns depth of tree
        int totalNodes();                                           // Returns total nodes
        int totalDataItems();                                       // Returns total data items
        void clear();                                               // Clear tree
        binaryTree<T>& operator<<(T d);                             // insertion operator
        void sort();


        // ____________________________________________________________FRIEND FNCTS / OPERATORS
        template<typename U>
        friend
        ostream& operator<<(ostream& out, binaryTree<U> &n);         // Extraction

        template<typename U>
        friend
        istream& operator>>(istream& in, binaryTree<U> &n);          // Insertion


    private://_________________________________________________PRIVATE DATA / FUNCTIONS
        node<T> *root;                                     // Pointer to root
        ORDER printOrder;                                  // Order of tree printing
        int depth(node<T> *r);                             // Depth ofthe tree starting from a node
        int totalNodes(node<T> *r);                        // Total nodes
        int totalDataItems(node<T> *r);                    // Total number of nodes items
        void nukem(node<T>* &r);                           // Deleting function
        void copy(node<T> *r);                             // Copying function
        void balance();                                    // Balance the tree
        void display(node<T> *r, ostream& out = cout);     // Display tree function
        int find(T d, node<T> *r);                         // Find function
        node<T>* findParent(node<T> *r, T d);              // Find parent of some node
        void insert(node<T> *r, node<T> *newNode);         // Inserting function
        node<T>* findLeftMost(node<T> *r);                 // Finding left most leaf
        node<T>* findRightMost(node<T> *r);                // Finding Right modt leaf

        ofstream BinarytTreeLog;
};


/*DEFUALT CONSTRUCTOR
 *USES:  root, printorder
*/
template<typename T>
binaryTree<T>::binaryTree()
{
    root = NULL;                                                    // Set root to node
    printOrder = IN_ORDER;                                          // Set printorder to IN_ORDER

    BinarytTreeLog.open("Bin.txt");
    BinarytTreeLog<<"BinaryTree constructed\n"<<
                    "root = NULL\n"<<
                    "printOrder = IN_ORDER\n";
     BinarytTreeLog.close();
}

template<typename T>
binaryTree<T>::binaryTree(T d, int c )
{                                                               // SINGLE DATA CONSTRUCTOR
    root = new node<T>(d,c);                                        // set root to a new node of data d, count c
    printOrder = IN_ORDER;                                          // set printorder to IN_ORDER

    BinarytTreeLog.open("Bin.txt");
    BinarytTreeLog<<"BinaryTree constructed\n"<<
                    "root = new node<T>("<<d<<","<<c<<")\n"<<
                    "printOrder = IN_ORDER\n";
     BinarytTreeLog.close();
}

template<typename T>
binaryTree<T>::~binaryTree()
{                                                               // DESTRUCTOR
    BinarytTreeLog<<"DESTRUCTOR FIRED"
                  <<"deleting from: "
                  <<root->data<<" ["<<root->count<<"]";
    nukem(root);                                                     // Call nukem starting from root
    BinarytTreeLog.close();
}


template<typename T>
binaryTree<T>::binaryTree(const binaryTree<T> &other)
{                                                               // COPY CONSTRUCTOR
    copy(other.root);                                               // call copy(other.root)
}


template<typename T>
binaryTree<T>& binaryTree<T>::operator=(const binaryTree<T> &other)
{                                                               // assignment operator
    if(this != &other)                                              // check if this tree is not the same as other
    {
        nukem(root);                                                // if not, nuke this tree
        copy(other.root);                                           // this tree copy the other tree
    }
    return *this;                                                   // return this tree
}


template<typename T>
void binaryTree<T>::insert(T d, int c)
{                                                               // INSERTING DATA D OF COUNT C
    node<T> *newNode = new node<T>(d,c);                            // create node consrtucted of data and count
    if(!root)                                                       // if the insert is for the first node
        root = newNode;                                             // let root be the new node
    else
        insert(root, newNode);                                      // otherwise insert newnode starting at root21
}


template<typename T>
bool binaryTree<T>::remove(T d)
{                                                                //REMOVE A SINGLE DATA D
    node<T> temp;                                                   // make temp node
    temp.left = temp.right = root;                                  // temp left and righ pointer point to root if exist
    node<T> *parent = findParent(&temp, d),                    // find the parent of the data d starting at temp
            *bye,
            *leftMost, *rightMost;



    if(!parent)// if the tree is empty, cannot remove
        return false;// return false remove
    if(d < parent->data)
    {
        bye = parent->left;
        bye->count--;
        if(int(bye->count) < 1)
        {
           if(bye->right)
           {
               parent->left = bye->right;
               leftMost = findLeftMost(bye->right);
               leftMost->left = bye->left;
           }
           else
              parent->left = bye->left;
           delete bye;
        }
    }
    else
    {
        bye = parent->right;
        bye->count--;
        if(int(bye->count) < 1)
        {
           if(bye->right)
           {
               parent->right = bye->right;
               leftMost = findLeftMost(bye->right);
               leftMost->left = bye->left;
           }
           else
              parent->right = bye->right;
           delete bye;
        }
    }
    root = temp.left;
    return true;
}


template<typename T>
int binaryTree<T>::find(T d)
{
    return find(d,root);
}


template<typename T>
ORDER binaryTree<T>::getTraversal()
{
    return printOrder;
}


template<typename T>
void binaryTree<T>::setTraversal(ORDER traversal)
{
    printOrder = traversal;
}


template<typename T>
int binaryTree<T>::depth()
{
    return depth(root);
}


template<typename T>
int binaryTree<T>::totalNodes()
{
    return totalNodes(root);
}


template<typename T>
int binaryTree<T>::totalDataItems()
{
    return totalDataItems(root);
}


template<typename T>
void binaryTree<T>::clear()
{
    nukem(root);
}


template<typename T>
binaryTree<T>& binaryTree<T>::operator<<(T d)
{
    insert(d);
    return *this;
}


template<typename T>
int binaryTree<T>::depth(node<T> *r)
{
    return r ? 1 + max(depth(r->left), depth(r->right)) : 0;
}

template<typename T>
int binaryTree<T>::totalNodes(node<T> *r)
{
    return r ? 1 + totalNodes(r->left) + totalNodes(r->right) : 0;
}


template<typename T>
int binaryTree<T>::totalDataItems(node<T> *r)
{
    return r ? r->count + totalDataItems(r->left) + totalDataItems(r->right) : 0;
}

template<typename T>
void binaryTree<T>::nukem(node<T>* &r)
{
    if(r)
    {
        nukem(r->left);
        nukem(r->right);
        delete r;
        r = NULL;
    }
}


template<typename T>
void binaryTree<T>::copy(node<T> *r)
{
    if(r)
    {
        insert(r->data, r->count);
        copy(r->left);
        copy(r->right);
    }

}


template<typename T>
void binaryTree<T>::display(node<T> *r, ostream& out)
{
    if(printOrder == PRE_ORDER)
        out<<r->data<<"["<<r->count<<"] ";

    if(r->left)
        display(r->left,out);

    if(printOrder == IN_ORDER)
        out<<r->data<<"["<<r->count<<"] ";

    if(r->right)
        display(r->right,out);

    if(printOrder == POST_ORDER)
        out<<r->data<<"["<<r->count<<"] ";

}


template<typename T>
int binaryTree<T>::find(T d, node<T> *r)
{
    return !r ? 0 :
                d == r->data ? r->count :
                d < r->data ? find(d, r->left) :
                              find(d, r->right);
}


template<typename T>
node<T>* binaryTree<T>::findParent(node<T> *r, T d)
{

    return !r ? NULL :// return null if empty
             r->left->data == d || r->right->data == d ? r // else if right or left node holds the data, return r being the parent
             :
             d < r->data ? findParent(r->left,d) // findParent(r->right,d) rather???
             :
             findParent(r->right,d); // findParent(r->left,d)??
}


template<typename T>
void binaryTree<T>::insert(node<T> *r, node<T> *newNode)
{
    if(newNode->data == r->data)
    {
        r->count += newNode->count;
        delete newNode;
        return;
    }
    if(newNode->data < r->data)
        if(!r->left)
            r->left = newNode;
        else
            insert(r->left,newNode);
    else
        if(!r->right)
            r->right = newNode;
        else
            insert(r->right, newNode);
     balance();

}

template<typename T>
void binaryTree<T>::balance()
{
    // sort my damn tree
}

template<typename T>
node<T>* binaryTree<T>::findLeftMost(node<T> *r)
{
    return !r ? NULL :
            r->left == NULL ? r :
            findLeftMost(r->left);
}


template<typename T>
node<T>* binaryTree<T>::findRightMost(node<T> *r)
{
    return !r ? NULL :
            r->right == NULL ? r :
            findRightMost(r->right);
}

template<typename U>
ostream& operator<<(ostream& out, binaryTree<U> &n)
{
    if(out != cout)
        out<<"Print order was: "<<n.printOrder<<endl;
    n.display(n.root, out);
    return out;
}

template<typename U>
istream& operator>>(istream& in, binaryTree<U> &n)
{
    U data;
    int count, printOrder;
    char junk;
    string line;
    stringstream ss;
    ORDER order[3] = {IN_ORDER, PRE_ORDER, POST_ORDER};
    if(in != cin)
    {
        getline(in, line);
        ss<<line.substr(line.find(':')+1);
        ss>>printOrder;
        n.printOrder = order[printOrder];
    }
    while(in>>data>>junk>>count>>junk)
        n.insert(data,count);
    return in;
}
// I love you mom, dad, sisters, friends and Rocio <3. Thank you guys.

#endif // BINARYTREE_H
