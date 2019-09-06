/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Daniel Guzman
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
    
  
    Node <T> *pCurrent = NULL;
    Node <T> *pTemp = NULL;
    Node <T> *pTemp2 = NULL;
    pCurrent = insert(array[0], pCurrent);
    int index = 0;
    
    for(int index = 1; index < num; index++)
    {
        
        insert(array[index],pCurrent);
        
       // exit = false;
        T temp;
        
        for (pTemp = pCurrent; pTemp!=NULL; pTemp = pTemp->pNext)
        {
            for (pTemp2 = pTemp->pNext; pTemp2!=NULL; pTemp2 = pTemp2->pNext)
            {
                
            if(pTemp->data > pTemp2->data)
            {
               // pCurrent = pCurrent->pNext;
                temp = pTemp->data;
                pTemp->data = pTemp2->data;
                pTemp2->data = temp;
            }
        }
    }

    }
    for (Node<T> * p = pCurrent; p; p = p->pNext)
        array[index++] = p->data;
    
}

#endif // INSERTION_SORT_H

