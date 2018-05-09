#ifndef HEAP_H
#define HEAP_H
#include <bits/stdc++.h>
#include "Task.h"
using namespace std;

class Heap
{
public:
    Heap();
    Task top();
    void push(Task);
    void pop();
    int size();
    void print();
    Task * heapSort();
    Task search (string); // return a Task with priority = -1 --- if not found a task with that name
    void loadFromFile(fstream &);
    void loadToFile(fstream &);
    ~Heap();
private:
    Task *v;
    int idx;
    int sizeInMemory;
    int left(int node);
    int right(int node);
    int perant (int node);
    void reheapUp(int node);
    void reheapDown(int node);

};

#endif // HEAP_H
