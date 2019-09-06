/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    This will contain the class definition of a Node.
 * Author
 *    Daniel Guzman
 ************************************************************************/
#ifndef node_h
#define node_h
#include <cassert>
#include <iostream>
using namespace std;
/*************************************************************************
 *  NODE: A node can be use as a linked list
 ************************************************************************/
template <class T>
class Node
{
public:
    Node(): data(0), pNext(NULL) {}
    Node(T newData):data(newData), pNext(NULL) {}
    
    T data;
    Node * pNext;
    
private:
    // No Private Variables in the Node
};
/*************************************************************************
 * COPY:
 * Copy a linked-list. Takes a pointer to a Node as a parameter and
 * returns a newly created linked-list containing a copy of all the
 * nodes below the list represented by the parameter. This should be
 * a non-member function
 ************************************************************************/
template<class T>
Node<T> * copy(Node<T> * & pHead) throw (const char*)
{
    
    Node<T> * orNode = pHead;
    Node<T> * pDestination = new Node<T>;
    
    pDestination->data = orNode->data;
    pDestination->pNext = NULL;
    
    Node<T> *const nodeHead = pDestination;
    
    orNode = orNode->pNext;
    
    while( orNode != NULL)
    {
        pDestination = pDestination->pNext = new Node<T>;
        pDestination->data = orNode->data;
        pDestination->pNext = NULL;
        orNode = orNode->pNext;
    }
    
    return nodeHead;
    
}
/*************************************************************************
 * INSERT:
 * Insert a new Node into the current linked-list. The first parameter
 * is the value to be placed in the new Node. The second parameter is
 * the Node preceding the new Node in the list. An optional third
 * parameter is set to true if the new item is to be at the head of the
 * list. This should be a non-member function.
 ************************************************************************/
template <class T>
Node<T> * insert(const T &t, Node<T> * & pNode, bool after = false)
{
    Node<T> * pNew = new Node<T>(t);
    
    if (after || pNode == NULL)
    {
        pNew->pNext = pNode;
        pNode = pNew;
    }
    else
    {
        pNew->pNext = pNode->pNext;
        pNode->pNext = pNew;
    }
    return pNew;
}
/*************************************************************************
 * FIND:
 * Find the Node corresponding to a given passed value from a given
 * linked-list. The first parameter is a pointer to the front of the
 * list, the second is the value to be found. The return value is a
 * pointer to the found node if one exists. This should be a non-member
 * function.
 ************************************************************************/
template<class T>
Node<T> * find( Node<T> * pHead, const T &t )
{
    if(pHead == NULL)
        return NULL;
    
    if(t == pHead->data)
        return pHead;
    else
        return find(pHead->pNext, t);
    return NULL;
    
}
/*************************************************************************
 * OPERATOR << :
 * Display the contents of a given linked-list.
 ************************************************************************/
template<class T>
ostream &operator << ( ostream &out, Node<T> * & rhs)
{
    for (Node<T> * p = rhs; p; p = p->pNext)
        out << p->data << (p->pNext == NULL ? "" : ", ");
    return out;
}
/*************************************************************************
 * FREEDATA:
 *  Release all the memory contained in a given linked-list. The one
 *  parameter is a pass-by-reference pointer to the head of the list.
 *  Once the memory is freed this function should set the parameter
 *  to NULL. This should be a non-member function.
 ************************************************************************/
template<class T>
void freeData(Node<T> * &  pHead)
{
    if(pHead == NULL)
        return;
    freeData(pHead->pNext);
    delete pHead;
    pHead = NULL;
}
#endif /* node_h */
