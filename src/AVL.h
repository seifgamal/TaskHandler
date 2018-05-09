#ifndef AVL_H
#define AVL_H
#include <bits/stdc++.h>
#include "AVLnode.h"
#include "Task.h"
#include "Tree.h"

using namespace std;

class AVL {
public:
	AVL();
	void insert(Task);
	void loadFromFile(fstream &f);
	void RemoveTopPriority();
	void print();
	Task search(string);
	~AVL();
private:

	AVLnode *root;
	void insert(AVLnode*, Task);
	void updateBalanceFactor(AVLnode*);
	void updatePathHeight(AVLnode*);
	void rotateLeft(AVLnode *);
	void rotateRight(AVLnode *);
	void removeByName(string);
	string MaxPriorityName(AVLnode *);
	void Inorder(AVLnode*);
	string name;
	int MAX;
};

#endif // BST_H
