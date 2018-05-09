#ifndef AVLnode_H
#define AVLnode_H
#include "Task.h"
using namespace std;
#include <bits/stdc++.h>

class AVLnode
{

public:
    AVLnode ();
    Task T;
    AVLnode * left;
    AVLnode * right;
    AVLnode * perant;
    int balanceFactor();
    void updateHeight();
    int height;
    int from;

    ~AVLnode();
    friend ostream& operator<< (ostream& out, AVLnode *AVLnode);
};
#endif // AVLnode_H
