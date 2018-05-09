#include "Heap.h"
#include "Task.h"

int Heap::left(int node)
{
    return node * 2 + 1;
}
int  Heap::right(int node)
{
    return node * 2 + 2;
}
int  Heap::perant (int node)
{
    if (node == 0)
        return -1;
    return (node - 1) / 2;
}
void  Heap::reheapUp(int node)
{
    if (perant(node) < 0 || v[node] <= v[perant(node)])
        return ;
    swap(v[perant(node)] , v[node]);
    reheapUp(perant(node));
}
void  Heap::reheapDown(int node)
{
    if (left(node) >= size())
        return;
    if (right(node) >= size() )
    {
        if ( v[left(node)] > v[node])
            swap(v[left(node)] , v[node]);
        return;
    }
    if (v[node].priority >= max(v[right(node)].priority, v[left(node)].priority))
        return ;

    if (v[right(node)] > v[left(node)])
    {
        swap(v[right(node)] , v[node]);
        reheapDown(right(node));
    }
    else
        swap(v[left(node)] , v[node]) , reheapDown(left(node));

}
 Heap::Heap()
{
    idx = sizeInMemory = 0;
    v = new Task ;
}
Task  Heap::top()
{
    if (size() == 0)
        assert(false);
    return v[0];
}
void  Heap::push(Task x)
{
    if (idx == sizeInMemory)
    {
        idx ++ , sizeInMemory ++ ;
        Task *temp = new Task[sizeInMemory];
        int i;

        for (i = 0 ; i < idx - 1 ; i++ )
        {
            temp[i] = v[i];
        }
        temp[i] = x;
        delete v;
        v = temp ;

    }
    else
    {
        v[idx] = x , idx ++;
    }
    reheapUp(size() - 1);
}
void  Heap::pop()
{
    if (size() == 0)
        assert(false);
    v[0] = v[size() - 1];
    idx -- ;
    reheapDown(0);
}
int  Heap::size()
{
    return idx;
}
void  Heap::print()
{
    cout << "You have  " << size() << " Tasks .. \n";
    for (int i = 0 ; i < size() ; i++ )
        cout << v[i] << "\n\t**************************\n";
    cout << "\n";
}
Task *  Heap::heapSort()
{
    Task *res = new Task[size()];
    for (int i = 0 ; i < size() ; i++ )
        res[i] = v[i];

    int index = 0 ;
    while (size())
    {
        res[index ++ ] = v[0] ;
        pop();
    }
    for (int i = 0 ; i < index ; i++)
    {
        push(res[i]);
    }
    return res;
}
Task Heap::search (string taskName)
{
    for (int i = 0 ; i < size() ; i ++ )
    {
        if (v[i].name == taskName)
        {
            cout << "Found .. \n";
            cout << v[i] ;
            return v[i];
        }
    }
    cout << "Not found .. \n";
    Task t;
    t.priority = -1;
    return t;
}
void  Heap::loadFromFile(fstream &f)
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
        push(t);
    }
}
void  Heap::loadToFile(fstream &f)
{
    f.open("My Tasks", ios::in | ios::out | ios::trunc);
    f << size();
    for (int i = 0 ; i < size() ; i++ )
    {
        f << v[i].name;
        f << v[i].description;
        f << v[i].priority;
        f << v[i].date;
        f << v[i].days;
    }

}
Heap::~Heap()
{
    delete v;
}
