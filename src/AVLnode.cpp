#include "AVLnode.h"
#include "Task.h"
using namespace std;
AVLnode::AVLnode()
{
    left = right = perant =  NULL;
    height = from = 0;
}
int AVLnode::balanceFactor()
{
    int l = 0, r = 0;
     if (left != NULL)
        l = left->height;

    if (right != NULL)
        r = right->height;

    return l - r ;
}
void AVLnode::updateHeight()
{
    int l = 0 , r = 0 ;
    if (left != NULL)
        l = left->height;

    if (right != NULL)
        r = right->height;

    height = 1 + max(l, r);
}
ostream& operator<< (ostream& out, AVLnode *AVLnode)
{
    out << endl ;
    out << AVLnode->T << endl ;
    out << "Height :" << AVLnode->height << endl;
    out << "Balance Factor :" << AVLnode->balanceFactor() << endl;

    return out;
}
AVLnode::~AVLnode()
{
}
