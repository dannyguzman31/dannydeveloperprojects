/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 * Summary:
 *    Create a binary search tree
 * Finished : Daniel Guzman
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator; 

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // constructor
   BST(): root(NULL){};
   
   // copy constructor
   BST(const BST & rhs);    
   
   ~BST();

   int  size() const  
  { 
      return empty() ? 0 : root->size(); 
  }   
   // determine if the tree is empty
   bool empty() const
   {
       return (root ==0);
   }

   // remove all the nodes from the tree.  Makes an empty tree.
   void clear()
   {
       deleteBinaryTree(root);
       root = NULL;
   }

   // overloaded assignment operator
   BST & operator = (const BST & rhs) throw (const char *)
   {

   	   /*
       if(this != &rhs)
       {
           if(root != NULL)
              deleteBinaryTree(root);
           if(rhs.root == NULL)
              root = NULL;
           else
              copyTree(this->root, rhs.root);
        }
       return *this;
       */

   		if(this != &rhs)
   		{
   			if(root != NULL)
   				deleteBinaryTree(root);
   			else
   				copyTree(this->root, rhs.root);
   		}
   		return *this;
   }
      
   // insert an item
   void insert(const T & t) throw (const char * );

   // remove an item
   void remove(BSTIterator <T> & it);

   // find a given item
   BSTIterator <T> find(const T & t);

   // the usual iterator stuff
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
private:

   BinaryNode <T> * root;

   void copyTree(BinaryNode<T> *& copNode, BinaryNode<T> * bNode)
    {
        if(bNode == NULL)
            copNode = NULL;
        else 
        {
            copNode = new BinaryNode<T>;
            copNode ->data = bNode ->data;
            copyTree(copNode->pLeft, bNode->pLeft);
            copyTree(copNode->pRight, bNode->pRight);
        }
    }

};

/*********************************************************
* copy constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST &rhs)
{
    copyTree(this->root, rhs.root);
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST()
{
    deleteBinaryTree(root);
    root == NULL;
}


/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{

    try
    {
        BinaryNode<T> * location = root;
        BinaryNode<T> * parent = 0;
        
        while (location != NULL  ) 
        {
            parent = location;
            if (t < location->data)
               location = location->pLeft;
            else
               location = location->pRight;
        }
        
        location = new BinaryNode<T>(t);
        if(parent == NULL)
            root = location;
        else if (t < parent->data)
        {
            parent->pLeft = location;
            location->pParent = parent;
        }
        else
        {
            parent->pRight = location;
            location->pParent = parent;
        }
        
    }
    catch(...)
    {
        throw "ERROR: Unable to allocate a node";
    }

}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
    BinaryNode<T> * node = it.getNode();
    BinaryNode<T> * parent = node->pParent;
    
    
    if (node->pLeft != 0 && node->pRight != 0 )
    {
        BinaryNode<T> * nodeSucc = node->pRight;
        parent = node;
        
        while( nodeSucc->pLeft != 0 )
        {
            parent = nodeSucc;
            nodeSucc = nodeSucc->pLeft;
        }
        node->data = nodeSucc->data;
        node = nodeSucc;

    }
    
    BinaryNode<T> * tree = node->pLeft;
    if ( tree == 0 )
    {
        tree = node->pRight;
    }
    if ( parent == 0 )
    {
        root = tree;
    }
    else if ( parent->pLeft == node )
    {
        parent->pLeft = tree;
    }
    else
    {
        parent->pRight = tree;
    }
    delete node;

}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
    BinaryNode<T> * fNode = root;
    bool dataFound = false;
    while(!dataFound && fNode != NULL)
    {
        if(t < fNode->data)
            fNode = fNode->pLeft;
        else if (fNode->data < t)
            fNode = fNode->pRight;
        else
        {
            dataFound = true;
        }
    }
    if(dataFound)
        return fNode;
    else
        return end();
}


/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfinode)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfinode)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFInode
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
      
   return *this;      
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFInode
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


#endif // BST_H
