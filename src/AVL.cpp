#include "AVL.h"
#include "Task.h"
#include <bits/stdc++.h>
using namespace std;
AVL::AVL() {
	root = NULL;
	MAX = 0;
	name = "default";
}
void AVL::insert(Task t) {
	// Handle the root ..
	if (root == NULL) {
		AVLnode *newAVLnode = new AVLnode;
		newAVLnode->T = t;
		root = newAVLnode;
	} else {
		insert(root, t);
	}
}
void AVL::insert(AVLnode* n, Task t) {
	if (n->T > t) { // add to left

		if (n->left == NULL) {
			AVLnode *newAVLnode = new AVLnode;
			newAVLnode->T = t;
			n->left = newAVLnode;
			newAVLnode->updateHeight();
			newAVLnode->perant = n;
			newAVLnode->from = -1;
		} else {
			insert(n->left, t);
		}
	} else { // add to right ..

		if (n->right == NULL) {
			AVLnode *newAVLnode = new AVLnode;
			newAVLnode->T = t;
			n->right = newAVLnode;
			newAVLnode->updateHeight();
			newAVLnode->perant = n;
			newAVLnode->from = 1;
		} else {
			insert(n->right, t);
		}
	}
	n->updateHeight();
	updateBalanceFactor(n);
}
void AVL::updateBalanceFactor(AVLnode *n) {
	if (n->balanceFactor() == -2) {
		if (n->right->balanceFactor() != -1) {
			AVLnode *node = new AVLnode;
			AVLnode *c = new AVLnode;
			node = n->right;
			c = n->right->left->right;

			n->right = n->right->left;
			n->right->perant = n;

			n->right->right = node;
			n->right->right->perant = node->right;
			n->right->right->left = c;
			n->right->from = 1;

			// update height ..
			n->right->right->updateHeight();
			n->right->updateHeight();
			n->updateHeight();
		}
		rotateLeft(n);
	}
	if (n->balanceFactor() == 2) {
		if (n->left->balanceFactor() != 1) {
			AVLnode *leftAVLnode = new AVLnode;
			leftAVLnode = n->left;
			AVLnode *b = n->left->right->left;

			n->left = n->left->right;
			n->left->perant = n;
			n->left->from = -1;
			n->left->left = leftAVLnode;
			leftAVLnode->perant = n->left;
			leftAVLnode->right = b;

			// update height ..
			n->left->left->updateHeight();
			n->left->updateHeight();
			n->updateHeight();

		}
		rotateRight(n);
	}
}

void AVL::rotateLeft(AVLnode *n) {

	if (n->from == 0) // it's a root ..
			{
		root = n->right;
	} else if (n->from == 1) // it comes from right ..
			{
		n->perant->right = n->right;
	} else
		n->perant->left = n->right;

	AVLnode *b = new AVLnode;
	AVLnode *oldAVLnode = new AVLnode;
	b = n->right->left;
	oldAVLnode = n;

	if (b != NULL)
		b->from = 1;

	n->right->from = n->from;
	n = n->right;
	n->left = oldAVLnode;
	n->left->right = b;
	n->left->from = -1;

	n->left->updateHeight();
	n->right->updateHeight();
	n->updateHeight();

}
void AVL::rotateRight(AVLnode *n) {
	if (n->from == 0) { // it's a root ..
		root = n->left;
	} else if (n->from == 1) { // it comes from right ..
		n->perant->right = n->left;
	} else
		n->perant->left = n->left;

	AVLnode* c = new AVLnode;
	c = n->left->right;

	if (c != NULL)
		c->from = -1;

	AVLnode* oldAVLnode = new AVLnode;
	oldAVLnode = n;

	n->left->from = n->from;
	n->left->perant = n->perant;
	n = n->left;
	n->right = oldAVLnode;
	oldAVLnode->left = c;
	n->right->from = 1;

	n->left->updateHeight();
	n->right->updateHeight();
	n->updateHeight();
}

Task AVL::search(string taskName) {
	Task t;
	AVLnode *node = new AVLnode;
	node = root;
	while (node != NULL) {
		if (node->T.name == taskName) {
			cout << "Found .. \n";
			return node->T;
		} else if (node->T.name > taskName) {
			node = node->left;
		} else {
			node = node->right;
		}
	}
	cout << "Not Found .. \n";
	return t;
}
void AVL::removeByName(string taskName) {
	AVLnode *node = new AVLnode;
	node = root;
	while (node != NULL) {
		if (node->T.name == taskName)
			break;
		else if (node->T.name > taskName)
			node = node->left;
		else
			node = node->right;
	}

	/// Has no children
	if (node->right == NULL && node->left == NULL) {
		if (node->from == 0) // it's a root
				{
			root = NULL;
		} else if (node->from == 1) // if comes from right
				{
			node->perant->right = NULL;
		} else
			// if comes from left
			node->perant->left = NULL;
		updatePathHeight(node->perant);
		delete node;
	} else if (node->from != 0 && (node->right == NULL || node->left == NULL)) {
		if (node->from == 1) // comes from right
				{
			if (node->left == NULL)
				node->right->perant = node->perant, node->perant->right =
						node->right;
			else
				node->left->perant = node->perant, node->right->from = 1, node->perant->right =
						node->left;
		} else // comes from left ..
		{
			if (node->right == NULL)
				node->left->perant = node->perant, node->perant->left =
						node->left;
			else
				node->right->perant = node->perant, node->right->from = -1, node->perant->left =
						node->right;
		}
		updatePathHeight(node->perant);
		delete node;
	} else {
		Task t;
		AVLnode *n = new AVLnode;
		n = node->right;
		if (n != NULL) {
			while (n->left != NULL)
				n = n->left;
		} else {
			n = node->left;
			if (n != NULL)
				while (n->right != NULL)
					n = n->right;
		}
		t = n->T;
		removeByName(t.name);
		node->T = t;
	}
}
void AVL::updatePathHeight(AVLnode* AVLnode) {
	if (AVLnode == NULL)
		return;
	AVLnode->updateHeight();
	updatePathHeight(AVLnode->perant);
}
void AVL::RemoveTopPriority() {
	name = MaxPriorityName(root);

	if (name != "default") {
		cout << "The removed Task's name is: " << name << " it's priority: "
				<< MAX << endl;
		removeByName(name);
	} else {
		assert("No Task to remove");
	}

	MAX = 0;
	name = "default";
}
string AVL::MaxPriorityName(AVLnode *n) {
	if (n == NULL)
		return name;
	MaxPriorityName(n->left);

	if (n->T.priority > MAX) {
		name = n->T.name;
		MAX = n->T.priority;
	}

	MaxPriorityName(n->right);
}
void AVL::loadFromFile(fstream &f) {
	f.seekp(0, ios::beg);
	int tasks;
	f >> tasks;
	while (tasks--) {
		Task t;
		getline(f, t.name);
		getline(f, t.description);
		string x;
		getline(f, x); // priority
		stringstream ss;
		ss << x;
		ss >> t.priority;
		ss.clear();
		getline(f, t.date);
		getline(f, x); // number of days
		ss << x;
		ss >> t.days;
		ss.clear();
		insert(t);
	}
}
void AVL::print() {
	Inorder(root);
}
void AVL::Inorder(AVLnode *n) {
	if (n == NULL)
		return;
	Inorder(n->left);
	cout << n->T << endl;
	Inorder(n->right);
}
AVL::~AVL() {
	//dtor
}
