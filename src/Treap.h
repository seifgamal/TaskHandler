#ifndef TREAP_H
#define TREAP_H
#include <bits/stdc++.h>
#include "Task.h"
#include "Node.h"
#include "Tree.h"
using namespace std;

class Treap {
public:
	Treap();
	void insert(Task);
	void print();
	void RemoveTopPriority();
	Task search(string);
	void loadFromFile(fstream &f);
	Node *root;
	~Treap();
protected:
private:

	void removeByName(string);
	void Inorder(Node*);
	void swapWithRight(Node *);
	void swapWithLeft(Node *);
	void rotate(Node*, char);
};

#endif // TREAP_H
