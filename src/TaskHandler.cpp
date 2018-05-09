//============================================================================
// Name        : TaskHandler.cpp
// Author      : seif
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include "Heap.h"
#include "Task.h"
#include "AVL.h"
#include "BST.h"
#include "Treap.h"

using namespace std;
fstream f;
void print() {
	cout << "Enter what you want to do .. \n\n";
	cout << "1) Loading Tasks from A file:\n";
	cout << "2) Insert new Task: \n";
	cout << "3) Delete Top priority: \n";
	cout << "4) Search for a Task: \n";
	cout << "5) Display Tasks: \n";
	cout << "5) Back: \n";
}

template<class Tree>
void printChoices(Tree h) {
	Task t;
	string taskName;
	int c;
	Here: cout << "Your choice: ";
	cin >> c;

	if (c == 1)
		h.loadFromFile(f);
	else if (c == 2) {
		cin >> t;
		h.insert(t);
	} else if (c == 3) {
		h.RemoveTopPriority();
	} else if (c == 4) {
		cin >> taskName;
		Task searchedT = h.search(taskName);
	} else if (c == 5) {
		h.print();
	} else
		return;
	cout << "\t\t\t\t\t\tDone ..\n";
	goto Here;
}
int main() {
	fstream f("My Tasks.txt");
	while (true) {
		cout << "\tchoose your Data structure ..\n\n";

		cout << "1) For Heap:.\n";
		cout << "2) For Binary Search Tree (BST): \n";
		cout << "3) For AVL: \n";
		cout << "4) For Treap: ..\n";
		cout << "5) For Exit: ..\n";

		int choose;
		cin >> choose;
		if (choose >= 1 && choose <= 4) {
			print();
		}
		if (choose == 1) {
			Task t;
			Heap h;
			string taskName;
			int c;
			Here: cout << "Your choice: ";
			cin >> c;

			if (c == 1)
				h.loadFromFile(f);
			else if (c == 2) {
				cin >> t;
				h.push(t);
			} else if (c == 3) {
				h.pop();
			} else if (c == 4) {
				cin >> taskName;
				Task searchedT = h.search(taskName);
			} else if (c == 5) {
				h.print();
			} else
				continue;
			cout << "\t\t\t\t\t\tDone ..\n";
			goto Here;
		}
		if (choose == 2) {
			BST h;
			printChoices(h);
		}
		if (choose == 3) {
			AVL h;
			printChoices(h);
		}
		if (choose == 4) {
			Treap h;
			printChoices(h);
		}
		if (choose == 5) {
			break;
		} else {
			cout << "Wrong choose\n\t\t Re- Enter \n";
		}
	}

	cout << "Thanks ..   \n";
	return 0;
}
