#ifndef BST_H
#define BST_H
#include <bits/stdc++.h>
#include "Node.h"
#include "Task.h"
#include "Tree.h"

using namespace std;

class BST
{
public:
    BST();
    void insert(Task);
    void RemoveTopPriority();
    Task search (string);
    void print();
    void loadFromFile(fstream &f);
    ~BST();
protected:
private:
    Node *root;
    void Inorder(Node*);
    string MaxPriorityName(Node *); // traverse in order
    void removeByName(string );
    string name;
    int MAX;
};

#endif // BST_H
