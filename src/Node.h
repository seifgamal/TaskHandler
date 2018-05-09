#ifndef NODE_H
#define NODE_H
using namespace std;
#include <bits/stdc++.h>
#include "Task.h"

class Node
{

public:
    Task T;
    Node * left;
    Node * right;
    Node * perant;
    int from ; // 0 if from nothing, 1 if from right, -1 if from left
    Node ();
    ~Node();
    friend ostream& operator<< (ostream& out, Node node);


};
#endif // NODE_H
