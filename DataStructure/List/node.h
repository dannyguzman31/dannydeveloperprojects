/***********************************************************************
 * Implementation:
 *    NODE
 * Summary:
 *
 * Author
 *    Daniel Guzman
 **********************************************************************/

#ifndef node_h
#define node_h
#include <iostream>
#include <string>

template <class T>
class Node {
    
    
public:
    
    Node() : data(0), pNext(NULL), pPrev(NULL) {};
    Node(T newData) : data(newData), pNext(NULL), pPrev(NULL){};
    
    T data;
    Node *pNext;
    Node *pPrev;
private:

    
    
};


#endif /* node_h */
