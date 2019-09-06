/***********************************************************************
 * Module:
 *    BST Node
 * Author:
 *    Daniel Guzman
 * Summary:
 *    This program will implement BST NODE
 ************************************************************************/

#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>


/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   // return size (i.e. number of nodes in tree)
   int size() const
   {
            return 1 +
               (pLeft== NULL? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
   }
   
   // Constructor and Destructor
    BinaryNode():pLeft(NULL), pRight(NULL),pParent(NULL), data(0){}
    BinaryNode(T newData):data(newData), pLeft(NULL), pRight(NULL), pParent(NULL){}
    
    
   // add a node the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;

   // the data of unknown type: cannot validate so is public
   T data;
};

/*****************************************
 * BINARYNODE :: ADDLEFT
 * Adds a value to the left
 ****************************************/
template <class T>
void BinaryNode<T> :: addLeft(BinaryNode <T> * pNode)
{
    if (pNode != NULL)
    {
        pNode->pParent = this;
    }
    
    pLeft = pNode;
}

/*****************************************
 * BINARYNODE :: ADDLEFT
 * Adds a BinaryNode to the left
 ****************************************/
template <class T>
void BinaryNode<T> :: addLeft(const T & t) throw (const char *)
{
    if (!t)
        return;
    
    try
    {
        BinaryNode<T> *pNew = new BinaryNode<T>(t);
        pNew->pParent = this;
        pLeft = pNew;
    }
    catch(...)
    {
        throw "ERROR: Unable to allocate a node";
    }
}

/*****************************************
 * BINARYNODE :: ADDRIGht
 * Adds a value to the right
 ****************************************/
template <class T>
void BinaryNode<T>:: addRight(BinaryNode<T> * pNode)
{
    
    if (pNode != NULL)
    {
        pNode->pParent = this;
    }
    
    pRight = pNode;
    
}

/*****************************************
 * BINARYNODE :: ADDRIGHT
 * Adds a BinaryNode to the right
 ****************************************/
template <class T>
void BinaryNode<T> :: addRight(const T & t) throw (const char *)
{
    
    if (!t)
        return;
    try
    {
        BinaryNode<T> * pNew = new BinaryNode<T>(t);
        pNew->pParent = this;
        pRight = pNew;
    }
    catch (...)
    {
        throw "ERROR: Unable to allocate a node:";
    }
}

/*****************************************
 * DELETEBINARYTREE
 * deletes the tree (recursive)
 ****************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T> * node)
{
    if(node != NULL)
    {
        deleteBinaryTree(node->pLeft);
        deleteBinaryTree(node->pRight);
        delete node;
        node = NULL;
        
    }
}

/*****************************************
 * OPERATOR <<
 * Display the contents of the BinaryNode
 ****************************************/
template <class T>
std::ostream & operator << (std::ostream &out , BinaryNode<T> * pStart)
{
    if (pStart != NULL)
    {
        out << pStart->pLeft;
        out << pStart->data << " ";
        out << pStart->pRight;
    }
    return out;
}
#endif // BNODE_H
