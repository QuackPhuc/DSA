#include <iostream>
#include <string>
#include "Tree.hpp"
using namespace std;

struct Tree
{
    Node *root;

    Tree() : root(nullptr) {};
    Tree(Node *root) : root(root) {};
    Tree(int array[], int size){
        root = new Node();
        build(root, array, 0, size - 1);
    }

    friend std::ostream &operator<<(std::ostream &stream, const Tree &tree){
        inOrder(tree.root, stream);
        return stream;
    }

    int height(){
        extern height(Node *root);
        return height(this -> root);
    }

};

int main()
{
    int array[] = {1,2,3,281,2,3,2,3,4,5,6,7,8};
    int n = sizeof(array)/sizeof(int);
    
    Tree tree = Tree(array, n);
    cout<<tree;
    cout<<endl;
    inOrder(tree.root);
    cout<<tree.height()<<endl;
    levelOrder(tree.root);
    return 0;
}

