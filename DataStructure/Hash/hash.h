/***********************************************************************
* Program:
*    Week 12, Hash
* Author: Daniel Guzman
*
************************************************************************/

#include <iostream>
using namespace std;

#ifndef HASH_H
#define HASH_H
#include "list.h"

template <class T>
ostream & operator << (ostream & out, List <T> & rhs)
{
   out << '{';

   ListIterator <T> it;
   for (it = rhs.begin(); it != rhs.end(); ++it)
      out << "  " << *it;

   out << "  }";

   return out;
}

template <class T>
class Hash  {
public:
   Hash() throw (const char *);
   Hash(const Hash<T> & rhs) throw (const char *);
   Hash(int cap) throw (const char *);
   ~Hash();
   Hash<T> & operator=(const Hash<T> &rhs) {
      clear();
      this->numBuckets = rhs.numBuckets;
      this->hSize = rhs.hSize;
      this->hashTable = new List<T>[numBuckets];
      for (int i = 0; i < capacity(); i++)
         this->hashTable[i] = rhs.hashTable[i];

      return *this;
   }
   virtual int hash(const T & value) const = 0;
   void insert(T item);
   bool find(T item);
   void clear();
   int size()  
   {
      return hSize;
   }
      int capacity() const 
   {
      return numBuckets;
   }
   bool empty()
   {
      return hSize == 0;
   }
   void  display()
   {
      cout << endl;
      for (int i = 0; i < capacity(); i++)
         cout << "Location: " << i << "::" << hashTable[i] << endl;
      cout << endl;
   }

private:
   List<T> * hashTable;  
   int numBuckets;     
   int hSize;       
};

/**************************************************
 * HASH COPY CONSTRUCTOR
 * Copy constructor for the hash class
 *************************************************/
template <class T>
Hash<T>::Hash(const Hash<T> & rhs) throw (const char *)  {
   try   {
      this->numBuckets = rhs.numBuckets;
      this->hSize = rhs.hSize;
      this->hashTable = new List<T>[numBuckets];

      for (int i = 0; i < numBuckets; i++)
         if(&rhs.hashTable[i] != NULL)
            hashTable[i] = rhs.hashTable[i];
   }
   catch(...) {
      throw "ERROR: unable to allocate memory for the hash";
   }
}
/**************************************************
 * HASH DEFAULT CONSTRUCTOR
 * Default constructor for the hash class
 *************************************************/
template <class T>
Hash<T>::Hash() throw (const char *)   {
   try {
      numBuckets = 11;
      hSize = 0;
      hashTable = new List<T>[numBuckets];

   }
   catch(...){
      throw "ERROR: unable to allocate memory for the hash";
   }
}

/**************************************************
 * HASH DECONSTRUCTOR
 * Deconstructor for the hash class
 *************************************************/
template <class T>
Hash<T>::~Hash()  {
   for (int i = 0; i < numBuckets; i++)
      hashTable[i].clear();
   numBuckets = 0;
   hSize = 0;
   delete[] hashTable;
}
/**************************************************
 * HASH NON-DEFAULT CONSTRUCTOR
 * Non-default constructor for the hash class
 *************************************************/
template <class T>
Hash<T>::Hash(int cap) throw (const char *)   {
   try {
      numBuckets = cap;
      hSize = 0;
      hashTable = new List<T>[numBuckets];
   }
   catch(...){
      throw "ERROR: unable to allocate memory for the hash";
   }
}

/**************************************************
 * HASH INSERT
 * Inserts values into the array
 *************************************************/
template <class T>
void Hash<T>::insert (T item) {
   int key = hash(item);

   if (key > -1 && key < numBuckets)
   {
         hashTable[key].push_back(item);
         hSize++;
   }
}

/**************************************************
 * HASH FIND
 * Finds an item in the array
 *************************************************/
 template <class T>
bool Hash<T>::find(T item)
{
   int key = hash(item);

   if (key > -1 && key < numBuckets)
   {
      ListIterator <T> it;
      for (it = hashTable[key].begin(); it != hashTable[key].end(); ++it)
      {
         if (*it == item)
            return true;
      }
   }
   return false;
}// find end

/**************************************************
 * HASH CLEAR
 * Clears the array
 *************************************************/
 template <class T>
 void Hash<T>::clear()  {
    if (!empty()) {
      for (int i = 0; i < numBuckets; i++)  {
         	hashTable[i].clear();
      }
      hSize = 0;
   }
}

#endif
