#include "Treap.h"
#include "Task.h"
#include <bits/stdc++.h>
using namespace std;

Treap::Treap()
{
    root = NULL;
}
void Treap::insert(Task t)
{
    Node *node = new Node;
    node->T = t;

    if (root == NULL)
    {
        root = node;
        return ;
    }
    Node *head = root;
    while(true)
    {
        if (head->T > node->T) // go to the left ..
        {
            if (head->left == NULL)
            {
                node->perant =  head;
                node->from = -1;
                head->left = node;

                while(node->perant != NULL && node->T.priority > node->perant->T.priority )
                    rotate(node,'L'); // rotate left ..

                return;
            }
            head = head->left;
        }
        else  // go to the right
        {
            if (head->right == NULL)
            {
                node->perant =  head;
                node->from = 1;
                head->right = node;
                while(node->perant != NULL && node->T.priority > node->perant->T.priority )
                    rotate(node,'R'); // rotate right

                return;
            }
            head = head->right;
        }
    }

}

void Treap::rotate(Node* node,  char choice) // L fro left .. R for Right ..
{
    if (node->perant->from != 0) // its parent not a root
    {
        if (node->perant->from == 1) // if comes from right
        {
            node->perant->right = node;
        }
        else
        {
            node->perant->left = node;
        }

    }
    else
        root = node;

    Node *temp = new Node;
    Node *perantNode = new Node;

    if (choice == 'L')
        temp = node->left;
    else
        temp = node->right;

    perantNode = node->perant;

    node->from = node->perant->from;
    node->perant = node->perant->perant;

    if (choice == 'L')
        node->left = perantNode;
    else
        node->right = perantNode;

    perantNode->from *= -1;
    perantNode->left = temp;

    if (temp != NULL)
        temp ->from *= -1;

}
void Treap::loadFromFile(fstream &f)
{
    f.seekp(0,ios::beg);
    int tasks;
    f >> tasks;
    while(tasks --)
    {
        Task t;
        getline(f,t.name);
        getline(f,t.description);
        string x;
        getline(f,x); // priority
        stringstream ss ;
        ss << x ;
        ss >> t.priority ;
        ss.clear();
        getline(f,t.date);
        getline(f,x); // number of days
        ss << x ;
        ss >> t.days ;
        ss.clear();
        insert(t);
    }
}
void Treap::print()
{
    Inorder(root);
}
void Treap::Inorder(Node *n)
{
    if (n == NULL)
        return ;
    Inorder(n->left);
    cout << n->T << endl;
    Inorder(n->right);
}
Task Treap:: search (string taskName)
{
    Task t;
    Node *node = new Node;
    node = root;
    while(node != NULL)
    {
        if (node->T.name == taskName)
        {
            cout << "Found .. \n";
            return node->T;
        }
        else if (node->T.name > taskName)
        {
            node = node->left ;
        }
        else
        {
            node = node->right ;
        }
    }
    cout << "Not Found .. \n";
    return t;
}

void Treap::RemoveTopPriority()
{
    Node *node = new Node ;
    node = root;

    if (root == NULL)
    {
        assert(false && "No Task to remove");
    }
    else if (root->left == NULL && root->right == NULL) // only root ..
    {
        root = NULL;
    }
    else if (root->left == NULL || root->right == NULL)
    {
        if (root->left != NULL)
        {
            root = root->left;
        }
        else
            root = root->right ;
        root->perant = NULL , root->from = 0;
        delete node;
    }
    else
    {
        if (node->right->T.priority >= node->left->T.priority)
            root = node->right;
        else
            root = node->left;

        while(node->left != NULL && node->right != NULL)
        {
            if (node->right->T.priority >= node->left->T.priority)
            {
                swapWithRight(node);
            }
            else
            {
                swapWithLeft(node);
            }
        }

        if (node->left != NULL)
        {
            node->left->perant = node->perant;
            if (node->from == 1)
                node->perant->right = node->left;
            else
                node->perant->left = node->left;
        }

        if (node->right != NULL)
        {
            node->right->perant = node->perant;
            if (node->from == 1)
                node->perant->right = node->right;
            else
                node->perant->left = node->right;
        }
        delete node;
    }
}
void Treap::swapWithRight(Node *node)
{

    if (node->perant != NULL) // its not a root ..
    {
        if (node->from == 1)
            node->perant->right = node->right;
        else
            node->perant->left = node->right;
    }

    node->right->perant = node->perant;
    node->perant = node->right;
    node->from = -1;

    Node * leftNode = new Node;
    leftNode = node->right->left;

    node->right->left = node;
    node->right = leftNode;

    if (leftNode != NULL)
    leftNode->from *= -1;

}
void Treap::swapWithLeft(Node *node)
{

    if (node->perant != NULL) // its not a root ..
    {
        if (node->from == 1)
            node->perant->right = node->left;
        else
            node->perant->left = node->left;
    }
    node->left->perant = node->perant;
    node->perant = node->left;
    node->from = 1;

    Node * RightNode = new Node;
    RightNode = node->right->left;

    node->left->right = node;
    node->left = RightNode;

     if (RightNode != NULL)
    RightNode->from *= -1;
}
Treap::~Treap()
{
    //dtor
}
