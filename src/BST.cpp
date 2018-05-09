#include "BST.h"
#include "Task.h"
#include <bits/stdc++.h>
using namespace std;
BST::BST()
{
    root = NULL;
    MAX = 0;
    name = "default";
}
void BST::insert(Task t)
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
                return ;
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
                return ;
            }
            head = head->right;
        }
    }
}

Task BST:: search (string taskName)
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
void BST::removeByName(string taskName)
{
    Node *node = new Node;
    node = root;
    bool found = 0;
    while(node != NULL)
    {
        if (node->T.name == taskName)
        {
            found = 1;
            break;
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
    if (!found)
    {
        cout << "Not Found .. \n";
        return;
    }
    /// Has no children
    if (node->from != 0 && node->right == NULL && node->left == NULL)
    {
        if (node->from == 0) // it's a root
        {
            root = NULL ;
        }
        else if (node->from == 1) // if comes from right
        {
            node->perant->right = NULL;
        }
        else  // if comes from left
            node->perant->left = NULL;
        delete node;
    }
    /// Has one children ..
    else if (node->from != 0 && (node->right == NULL || node->left == NULL))
    {
        if (node->from == 1) // comes from right
        {
            if (node->left == NULL)
                node->right->perant = node->perant,
                             node->perant->right = node->right;
            else
                node->left->perant = node->perant,
                            node->right->from = 1,
                                         node->perant->right = node->left;
        }
        else // comes from left ..
        {
            if (node->right == NULL)
                node->left->perant = node->perant,
                            node->perant->left = node->left;
            else
                node->right->perant = node->perant,
                             node->right->from = -1 ,
                                          node->perant->left = node->right;
        }
        delete node;


    }
    /// Has both
    else
    {
        Task t;
        Node *n = new Node;
        n = node->right ;
        if (n != NULL)
        {
            while(n->left != NULL)
                n = n->left;
        }
        else
        {
            n = node->left ;
            if (n != NULL)
                while(n->right != NULL)
                    n = n->right;
            else
            {
                root = NULL;
                return;
            }
        }
        t = n->T;
        removeByName(t.name);
        node->T = t;
    }
}
void BST::RemoveTopPriority()
{
    name = MaxPriorityName(root);

    if (name != "default")
    {
        cout << "The removed Task's name is: " << name << " it's priority: " << MAX << endl;
        removeByName(name);
    }
    else
    {
        assert("No Task to remove");
    }

    MAX = 0;
    name = "default";
}
string BST::MaxPriorityName(Node *n)
{
    if (n == NULL)
        return name;
    MaxPriorityName(n->left);

    if (n->T.priority > MAX)
    {
        name = n->T.name;
        MAX = n->T.priority;
    }

    MaxPriorityName(n->right);
}
BST::~BST()
{
    //dtor
}
void BST::loadFromFile(fstream &f)
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
void BST::print()
{
    Inorder(root);
}
void BST::Inorder(Node *n)
{
    if (n == NULL)
        return ;
    Inorder(n->left);
    cout << n->T << endl;
    Inorder(n->right);
}
