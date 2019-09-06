/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Class LIST and necessary ListIterators
 *    Creates a Doublely Linked LIST
 *    Iterators help in navigating the LIST
 * Author
 *   Daniel Guzman - I used my list from the previous sections
 ************************************************************************/

#include <iostream>
#include <string>

using namespace std;



#ifndef WEEK07_LIST_H
#define WEEK07_LIST_H
template <class T>
class ListIterator;

template <class T>
class ListConstIterator;

template <class T>
class Node {
public:
   Node() : data(0), pNext(0), pPrev(0) {};
   Node(T newData){
      data = newData;
      pNext = 0;
      pPrev = 0;
   }

   T data;
   Node<T> * pNext;
   Node<T> * pPrev;
};


template <class T>
class List {

private:
   int length;

   Node<T> *pHead;
   Node<T> *pTail;
public:
   // Default constructor
   List() throw(const char *) {
      try {
         pHead = NULL;
         pTail = NULL;
         length = 0;
      }
      catch (...) {
         throw "ERROR: unable to allocate a new node for a list";
      }
   };

   // Copy Constructor
   List(const List<T> &rhs) throw(const char *) {
      try {
         this->pHead = NULL;
         this->pTail = NULL;
         this->length = 0;
         *this = rhs;
      }
      catch (...) {
         throw "ERROR: unable to allocate a new node for a list";
      }
   }

   // Destructor
   ~List() { clear(); }

   //  List Class insert function... uses iterator to position insert of new node
   ListIterator<T> insert(ListIterator<T> & it, const T & data) throw (const char *);

   // List class remove function... uses ListIterator to get to the node that needs to be deleted
   ListIterator<T> remove(ListIterator<T> &) throw (const char *);

   // return an iterator to the beginning of the Set
   ListIterator<T> begin() { return ListIterator<T>(pHead); }

   // return an iterator to the end of the Set
   ListIterator<T> end() { return ListIterator<T>(NULL); }

   // return an iterator to the beginning of the Set
   ListIterator<T> rbegin() { return ListIterator<T>(pTail); }

   // return an iterator to the end of the Set
   ListIterator<T> rend() { return ListIterator<T>(NULL); }

   // returns the length of the List
   int size() { return length; };

   // returns true if length is 0
   bool empty() { return length == 0; }

   // data reference to first node in the list
   T & front() throw(const char *) {
      if (pHead != NULL)
         return pHead->data;
      else
         throw "ERROR: unable to access data from an empty list";
   }

   // data reference to last node in list
   T & back() throw(const char *) {
      if (pHead != NULL)
         return pTail->data;
      else
         throw "ERROR: unable to access data from an empty list";
   }

   void freeData(Node<T> *&pHead) {

      if (pHead == NULL)
         return;
      freeData(pHead->pNext);
      delete pHead;
      pHead = pTail = NULL;
      length = 0;
   }

   void clear() {
      freeData(pHead);
   }

   void push_front(const T &data) throw(const char *) {
      try {
         Node<T> *pNew = new Node<T>(data);
         pNew->pNext = pHead;
         if (pHead != NULL)
            pHead->pPrev = pNew;
         else
            pTail = pNew;
         pHead = pNew;
         length++;
      }
      catch (...) {
         throw "ERROR: unable to allocate a new node for a list";
      }
   }

   void push_back(const T &data) {
      try {
         Node<T> *pNew = new Node<T>(data);
         pNew->pPrev = pTail;
         if (pTail != NULL)
            pTail->pNext = pNew;
         else
            pHead = pNew;
         pTail = pNew;
         length++;
      }
      catch (...) {
         throw "ERROR: unable to allocate a new node for a list";
      }
   }
  
   List<T> &operator=(const List<T> &rhs) {
      clear();
      for (Node<T> *p = rhs.pHead; p; p = p->pNext) {
         push_back(p->data);
      }
      return *this;
   }

};

/**************************************************
 * List ITERATOR
 * An iterator through List
 *************************************************/
template <class T>
class ListIterator
{
public:
   friend ListIterator<T> List<T>::remove(ListIterator<T> & it) throw (const char *);
   // default constructor
   ListIterator() : p(NULL) {}

   // initialize to direct p to some item
   ListIterator(Node<T> * p) : p(p) {}

   // copy constructor
   ListIterator(const ListIterator<T> & rhs) { *this = rhs; }

   // assignment operator overload
   ListIterator<T> & operator = (const ListIterator<T> & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator overload
   bool operator != (const ListIterator<T> & rhs) const
   {
      return rhs.p != this->p;
   }

   // equals operator overload
   bool operator == (const ListIterator<T> & rhs) const
   {
      return (rhs.p == this->p);
   }

   // dereference operator operator overload
   T & operator * () throw (const char *)
   {
      if(p)
         return p->data;
      else
         throw "ERROR: Trying to dereference a NULL pointer";
   }

   // prefix increment operator overload
   ListIterator <T> & operator ++ ()
   {
      p=p->pNext;
      return *this;
   }

   // prefix decrement operator overload
   ListIterator <T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment operator overload
   ListIterator <T> operator++(int postfix)
   {
      ListIterator<T> tmp(*this);
      p = p->pNext;
      return tmp;
   }
   // postfix decrement operator overload
   ListIterator <T> operator--(int postfix)
   {
      ListIterator<T> tmp(*this);
      p = p->pPrev;
      return tmp;
   }

   Node <T> * p;
};

/**************************************************
 * List CONST ITERATOR
 * An iterator through List
 *************************************************/
template <class T>
class ListConstIterator
{
   friend ListIterator<T> List<T>::remove(ListIterator<T> & it) throw (const char *);
public:
   // default constructor
   ListConstIterator() : p(NULL) {}

   // initialize to direct p to some item
   ListConstIterator(const Node<T> * p) : p(p) {}

   // copy constructor
   ListConstIterator(const ListConstIterator<T> & rhs) { *this = rhs; }

   // assignment operator
   ListConstIterator<T> & operator = (const ListConstIterator<T> & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator overload
   bool operator != (const ListConstIterator<T> & rhs) const
   {
      return rhs.p != this->p;
   }
  // equals operator overload
   bool operator == (const ListConstIterator<T> & rhs) const
   {
      return (rhs.p == this->p);
   }

   // dereference operator overload
   T operator * () const
   {
      return p->data;
   }

   // prefix increment operator overload
   ListConstIterator <T> & operator ++ ()
   {
      p=p->pNext;
      return *this;
   }

   // prefix decrement operator overload
   ListConstIterator <T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment operator overload
   ListConstIterator <T> operator++(int postfix)
   {
      ListConstIterator<T> tmp(*this);
      p = p->pNext;
      return tmp;
   }
   // postfix decrement operator overload
   ListConstIterator <T> operator--(int postfix)
   {
      ListConstIterator<T> tmp(*this);
      p = p->pPrev;
      return tmp;
   }

private:
   const Node<T> * p;
};

template <class T>
ListIterator<T> List<T>::remove(ListIterator<T> & it) throw (const char *)
{
   ListIterator<T> itNext = end();

   if (it == end())
      throw "ERROR: unable to remove from an invalid location in a list";

   if(it.p->pNext)
   {
      it.p->pNext->pPrev = it.p->pPrev;
      itNext = it.p->pNext;
   }
   else
   {
      pTail = pTail->pPrev;
   }

   if(it.p->pPrev)
   {
      it.p->pPrev->pNext = it.p->pNext;
   }
   else
   {
      pHead = pHead->pNext;
   }

   delete it.p;
   length--;
   return itNext;
}

template <class T>
ListIterator<T> List<T>::insert(ListIterator<T> & it, const T & data) throw (const char *)
{

   if (pHead == NULL)
   {
      pHead = pTail = new Node <T> (data);
      return begin();
   }

   try
   {
      Node <T> * pNew = new Node <T> (data);
      if (it == end())
      {
         pTail->pNext = pNew;
         pNew->pPrev = pTail;
         pTail = pNew;
         it = pNew;
      }
     else
      {
         pNew->pPrev = it.p->pPrev;
         pNew->pNext = it.p;
         if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
         else
            pHead = pNew;
         if (pNew->pNext)
            pNew->pNext->pPrev = pNew;
         else
            pTail = pNew;
         it = pNew;
      }
      length++;
   }
   catch (...)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}


#endif 
