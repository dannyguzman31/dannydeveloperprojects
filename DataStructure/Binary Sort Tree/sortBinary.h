/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST<T> * sort = new BST<T>;
   for(int i = 0 ; i < num ; i++ )
      sort->insert(array[i]);

   int i = 0;
   BSTIterator <T> it;
   for (it = sort->begin(); it != sort->end(); ++it)
   {
      array[i] = it.operator*();
      i++;
   }
}


#endif // SORT_BINARY_H
