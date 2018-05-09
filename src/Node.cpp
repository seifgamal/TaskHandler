#include "Node.h"
#include "Task.h"

Node::Node()
{
    left = right = perant =  NULL;
    from = 0;
}
ostream& operator<< (ostream& out, Node node)
{
    out << endl ;
    out << node.T << endl ;
    return out;
}
Node::~Node()
{
}
