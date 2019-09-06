//
//  set.h
//  W5_Set
//
//  Created by Daniel Guzman on 10/11/17.
//  Copyright © 2017 Daniel Guzman. All rights reserved.
//

#ifndef set_h
#define set_h
#include <cassert>
/*****************************************
 * Set
 * Just like the std :: Set <T> class
 ****************************************/
template <class T>
class Set
{
public:
    // constructors and destructors
    Set() : data(NULL), numElements(0), numCapacity(0){}
    Set(int numCapacity) throw (const char *);
    Set(const Set <T> & rhs) throw (const char *);
    ~Set();
    
    //assignment operator
    Set <T> & operator = (const Set <T> & rhs) throw (const char *);
    
    //union, difference, and intersection
    Set <T> & operator || (const Set <T> & rhs) throw (const char *);
    Set <T> & operator &&(const Set <T> & rhs) throw (const char *);
    Set <T> & operator -(const Set <T> & rhs) throw (const char *);
    
    // standard container interfaces
    int  size() const { return numElements;}
    bool empty() const { return size() == 0;}
    void clear() {numElements = 0;}
    
    // the various iterator interfaces
    class iterator;
    class const_iterator;
    iterator begin(){ return iterator(data);}
    iterator end(){ return iterator(data + numElements);}
    const_iterator cbegin() const { return const_iterator (data);}
    const_iterator cend() const { return const_iterator (data + numElements);}
    iterator find(const T & t);
    
    //typical Set methods
    void insert(const T & t) throw (const char *);
    void erase(iterator & it) throw (const char *);
    Set <T> & unions(const Set <T> & rhs);
    Set <T> & intersection(const Set <T> & rhs);
    Set <T> & difference(const Set <T> & rhs);
    int capacity() { return numCapacity; }
    
private:
    T *  data;                 // user data, a dynamically-allocated array
    int  numCapacity;          // the capacity of the array
    int  numElements;          // the number of items currently used
    void resize(int newCapacity) throw (const char *);
    int findIndex(const T &t);
    bool found;
};

/*****************************************
 * NON-DEFAULT constructors
 * non-default constructor: Set the capacity initially
 ****************************************/
template <class T>
Set <T> :: Set(int numCapacity) throw (const char *) : data(NULL), numElements(0), numCapacity(0)
{
    assert(numCapacity >= 0);
    
    // do nothing if there is nothing to do.
    // since we can't grow an array, this is kinda pointless
    if (numCapacity == 0)
    {
        this->numCapacity = 0;
        data = NULL;
        return;
    }
    else
    {
        this->numCapacity = numCapacity;
    }
    
    // attempt to allocate
    try
    {
        T t;
        data = new T[numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    
}

/*****************************************
 * COPY CONSTRUCTOR
 ****************************************/
template <class T>
Set <T> :: Set (const Set <T> & rhs) throw (const char *) : data(NULL), numElements(0), numCapacity(0)
{
    if (!rhs.empty())
        *this = rhs; // call the assignment operator
}

/*****************************************
 * DESTRUCTOR
 ****************************************/
template <class T>
Set <T> :: ~Set()
{
    if (size() != 0)
        delete [] data;
}

/***************************************
 * Set <T> :: RESIZE
 * This method will grow the current buffer
 * to newCapacity.  It will also copy all
 * the data from the old buffer into the new
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 *     THROW  : ERROR: Unable to allocate a new buffer for Set
 **************************************/
template <class T>
void Set <T> :: resize(int newCapacity) throw (const char *)
{
    assert(newCapacity > 0 && newCapacity > numCapacity);
    
    // allocate the new array
    T * pNew;
    try
    {
        pNew = new T[newCapacity];       // could throw bad_alloc
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for vector";
    }
    
    // copy over the data from the old array
    for (int i = 0; i < numElements; i++)
        pNew[i] = data[i];
        
        // delete the old and assign the new
        if (NULL != data)
            delete [] data;
    data = pNew;
    numCapacity = newCapacity;
}

/***************************************
 * Set <T> :: assigment operator
 * This operator will copy the contents of the
 * rhs onto *this, growing the buffer as needed
 *     INPUT  : rhs the Set to copy from
 *     OUTPUT : *this
 **************************************/
template <class T>
Set <T> & Set <T> :: operator = (const Set <T> & rhs)
throw (const char *)
{
    if (&rhs == this)
        return *this;
    
    // blow away anything that was in this->data previously
    numElements = 0;
    
    // make sure we are big enough to handle the new data
    if (rhs.numElements > numCapacity)
        resize(rhs.numElements);
        assert(numCapacity >= rhs.numElements);
        
        // copy over the data from the right-hand-side
        numElements = rhs.numElements;
        for (int i = 0; i < rhs.numElements; i++)
            data[i] = rhs.data[i];
            
            // return self
            return *this;
}
/**************************************************
 * Set ITERATOR
 * An iterator through Set.  You only need to
 * support the following:
 *   1. Constructors (default and copy)
 *   2. Not equals operator
 *   3. Increment (prefix and postfix)
 *   4. Dereference
 * This particular iterator is a bi-directional meaning
 * that ++ and -- both work.  Not all iterators are that way.
 *************************************************/
template <class T>
class Set <T> :: iterator
{
public:
    // constructors, destructors, and assignment operator
    iterator()      : p(NULL) {}
    iterator(T * p) : p(p)    {}
    iterator(const iterator & rhs) { *this = rhs; }
    iterator & operator = (const iterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    // equals, not equals operator
    bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
    bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
    
    // dereference operator
    T & operator * ()
    {
        if (p)
            return *p;
        else
            throw "ERROR: Trying to dereference a NULL pointer";
    }
    
    // prefix increment
    iterator & operator ++ ()
    {
        p++;
        return *this;
    }
    
    // postfix increment
    iterator operator ++ (int postfix)
    {
        iterator tmp(*this);
        p++;
        return tmp;
    }
    
    // prefix decrement
    iterator & operator -- ()
    {
        p--;
        return *this;
    }
    
    // postfix decrement
    iterator operator -- (int postfix)
    {
        iterator tmp(*this);
        p--;
        return tmp;
    }
    
private:
    T * p;
};

/**************************************************
 * Set CONSTANT ITERATOR
 * An iterator through Set where we cannot change
 * the Set with *it
 *
 * The only difference between this and SetIterator
 * is that the pointer member variable is a const and
 * the dereference operator returns const by-reference
 *************************************************/
template <class T>
class Set <T> :: const_iterator
{
public:
    // constructors, destructors, and assignment operator
    const_iterator()      : p(NULL) {}
    const_iterator(T * p) : p(p)    {}
    const_iterator(const const_iterator  & rhs) { this->p = rhs.p; }
    const_iterator & operator = (const const_iterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    // not equals operator
    bool operator != (const const_iterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // equals operator
    bool operator == (const const_iterator & rhs) const
    {
        return rhs.p == this->p;
    }
    
    // dereference operator
    const T operator * () const
    {
        return *p;
    }
    
    // prefix increment
    const_iterator & operator ++ ()
    {
        p++;
        return *this;
    }
    
    // postfix increment
    const_iterator operator ++ (int postfix)
    {
        Set <T> :: const_iterator tmp(*this);
        p++;
        return tmp;
    }
    // prefix decrement
    const_iterator & operator -- ()
    {
        p--;
        return *this;
    }
    
    // postfix decrement
    const_iterator operator -- (int postfix)
    {
        const_iterator tmp(*this);
        p--;
        return tmp;
    }
    
private:
    const T * p;
};

/***************************************
 * Set :: find
 * Find if a given element is in the Set.
 * If it is, return the iterator to it.
 * If not, return the NULL iterator.
 **************************************/
template <class T>
typename Set <T> :: iterator Set <T> :: find(const T &t)
{
    int iFirst = 0;
    int iLast = numElements - 1;
    
    while(iFirst <= iLast)
    {
        int iMiddle = (iFirst + iLast) / 2;
        
        if(data[iMiddle] == t)
            return iterator(data + iMiddle);
        if(data[iMiddle] > t)
            iLast = iMiddle - 1;
        else
            iFirst = iMiddle + 1;
    }
    
    //The item was not found.
    return end();
}

template <class T>
int Set <T> :: findIndex(const T &t)
{
    int iFirst = 0;
    int iLast = numElements - 1;
    
    while(iFirst <= iLast)
    {
        int iMiddle = (iFirst + iLast) / 2;
        
        if(data[iMiddle] == t)
            return iMiddle;
        if(data[iMiddle] > t)
            iLast = iMiddle - 1;
        else
            iFirst = iMiddle + 1;
    }
    
    //The item was not found.
    return iFirst;
}

/***************************************
 * Set :: insert
 * Insert an item on the end of the Set.
 **************************************/
template <class T>
void Set <T> :: insert(const T &t) throw(const char *)
{
    if (size() == numCapacity)
    {
        if(numCapacity == 0)
            resize(1);
            else
                resize(numCapacity * 2);
                }
    
    int iInsert = findIndex(t);
    if(data[iInsert] != t)
    {
        for(int i = numElements; i >= iInsert; i--)
        {
            data[i + 1] = data[i];
        }
        data[iInsert] = t;
        numElements++;
    }
}

/***************************************
 * Set :: erase
 * Erase an item on the end of the Set.
 **************************************/
template <class T>
void Set <T> :: erase(iterator &it) throw (const char *)
{
    int index = 0;
    
    if(data[index] != *it)
        index++;
    for(int i = 0; i < (size() - index); i++)
        data[index + i] = data[index + i+ 1];
        numElements--;
    
}

/***************************************
 * Set :: union
 **************************************/
template <class T>
Set <T> & Set <T> :: operator || (const Set <T> & rhs) throw (const char *)
{
    int iSet1 = 0;
    int iSet2 = 0;
    
    T *pNew;
    try
    {
        pNew = new T[numCapacity + rhs.numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for vector";
    }
    
    
    while(iSet1 < numElements || iSet2 < rhs.numElements)
    {
        if(iSet1 == numElements)
            pNew[iSet1] = rhs.data[iSet2++];
            else if(iSet2 == rhs.numElements)
                pNew[iSet2] = data[iSet1++];
                else if(data[iSet1] == rhs.data[iSet2])
                {
                    pNew[iSet1] = data[iSet1];
                    iSet1++;
                    iSet2++;
                }
                else if(data[iSet1] < data[iSet2])
                    pNew[iSet1] = data[iSet1++];
                    else
                        pNew[iSet2] = rhs.data[iSet2++];
                        
                        data = pNew;
                        //return *this;
                        }
    return *this;
}

/***************************************
 * Set :: intersection
 **************************************/
template <class T>
Set <T> & Set <T> :: operator &&(const Set <T> & rhs) throw (const char *)
{
    int iSet1 = 0;
    int iSet2 = 0;
    
    T *pNew;
    try
    {
        pNew = new T[numCapacity + rhs.numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for vector";
    }
    
    while(iSet1 < numElements || iSet2 < rhs.numElements)
    {
        if(iSet1 == numElements)
            return *this;
        else if(iSet2 == rhs.numElements)
            return *this;
        else if(data[iSet1] == rhs.data[iSet2])
        {
            pNew[iSet1] = data[iSet1];
            iSet1++;
            iSet2++;
        }
        else if(data[iSet1] < data[iSet2])
            iSet1++;
        else
            iSet2++;
        
        data = pNew;
        //return *this;
    }
    return *this;
}

/*************************************
 * Set :: difference
 **************************************/
template <class T>
Set <T> & Set <T> :: operator -(const Set <T> & rhs) throw (const char *)
{
    int iSet1 = 0;
    int iSet2 = 0;
    
    T *pNew;
    try
    {
        pNew = new T[numCapacity + rhs.numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for vector";
    }
    
    while(iSet1 < numElements || iSet2 < rhs.numElements)
    {
        if(iSet1 != numElements)
            return *this;
        else if(iSet2 != rhs.numElements)
            return *this;
        else if(data[iSet1] != rhs.data[iSet2])
        {
            pNew[iSet1] = data[iSet1];
            iSet1++;
            iSet2++;
        }
        else if(data[iSet1] < data[iSet2])
            iSet1++;
        else
            iSet2++;
        
        data = pNew;
        // return *this;
    }
    return *this;
}


#endif /* set_h */
