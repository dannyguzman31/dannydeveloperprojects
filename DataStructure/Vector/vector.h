/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This will contain the class definition of:
 *        Vector                 : A class that represents a Vector
 *        Vector::iterator       : An interator through Vector
 *        Vector::const_iterator : A constant iterator
 * Author
 *    Daniel Guzman
 * Time: Took about 6 hours of work to do it.
 * 
 ************************************************************************/
#ifndef vector_h
#define vector_h

#include <iostream>
#include <string>
#include <cassert>



/*********************************************************
 * VECTOR
 * A vector is an array-like data-structure containing
 * a collection of elements each referenced with an
 * index. Vectors are different from arrays in that
 * the capacity can increase at run-time
 ********************************************************/
    
template <class T>
class Vector {
        
public:
    // constructors and destructors
    Vector() :
    data(NULL), numElements(0), numCapacity(0) {}
    Vector(int numElements             ) throw (const char *);
   // Vector(int numElements, const T & t) throw (const char *);
    Vector(const Vector <T> & rhs      ) throw (const char *);
    ~Vector();
    Vector <T> & operator = (const Vector <T> & rhs) throw (const char *);
    
    // standard container interfaces
    int  size()             const { return numElements;      }
    int  capacity()         const { return numCapacity;      }
    bool empty()            const { return numElements == 0; }
    void clear()                  { numElements = 0;         }
    
    // Vector-specific interfaces
    void push_back(const T & t)       throw (const char *);
    T & operator [] (int index)       throw (const char *);
    T   operator [] (int index) const throw (const char *);
    
    // the various iterator interfaces
    class iterator;
    class const_iterator;
    iterator       begin()        { return iterator       (data);              }
    iterator       end()          { return iterator       (data + numElements);}
    const_iterator cbegin() const { return const_iterator (data);              }
    const_iterator cend()   const { return const_iterator (data + numElements);}
    
private:
    T *  data;                 // user data, a dynamically-allocated array
    int  numCapacity;          // the capacity of the array
    int  numElements;          // the number of items currently used
    void resize(int newCapacity, const T & t) throw (const char *);
    void resize(int newCapacity)              throw (const char *);
};


/*****************************************
 * NON-DEFAULT constructors
 *set the capacity initially
 ****************************************/
template <class T>
Vector <T> :: Vector(int numElements) throw (const char *) :
data(NULL), numElements(0), numCapacity(0)
{
        resize(numElements);
        //this->numElements = numElements;  
}

/*****************************************
 * COPY CONSTRUCTOR
 ****************************************/
template <class T>
Vector <T> :: Vector (const Vector <T> & rhs) throw (const char *) :
data(NULL), numElements(0), numCapacity(0)
{
    if (!rhs.empty())
        *this = rhs;
}

/*****************************************
 * DESTRUCTOR
 ****************************************/
template <class T>
Vector <T> :: ~Vector()
{
    if (numCapacity != 0)
        delete [] data;
}

/*****************************************
 * ARRAY - ACCESS
 * Read-Write acess
 ****************************************/
template <class T>
T & Vector <T> :: operator [] (int index) throw (const char *)
{
    if (index < 0 || index >= numElements)
        throw "ERROR: Invalid index";
    return data[index];
}

/******************************************
 * ARRAY - ACCESS
 * READ-ONLY ACCESS
 *****************************************/
template <class T>
T Vector <T> :: operator [] (int index) const throw (const char *)
{
    if (index < 0 || index >= numElements)
        throw "ERROR: Invalid index";
    return data[index];
}


/**************************************************
 * Vector ITERATOR
 *************************************************/
template <class T>
class Vector <T> :: iterator
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
 * Vector CONSTANT ITERATOR
 *************************************************/
template <class T>
class Vector <T> :: const_iterator
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
        Vector <T> :: const_iterator tmp(*this);
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
 * Vector <T> :: RESIZE
 * This method will grow the current buffer
 * to newCapacity.
 **************************************/
template <class T>
void Vector <T> :: resize(int newCapacity, const T & t) throw (const char *)
{
    
    T * pNew;
    try
    {
        pNew = new T[newCapacity];       // could throw bad_alloc
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for Vector";
    }
    
   
    for (int i = 0; i < numElements; i++)
        pNew[i] = data[i];
        for (int i = numElements; i < newCapacity; i++)
            pNew[i] = t;
            
            // delete the old and assign the new
            if (NULL != data)
                delete [] data;
    data = pNew;
    numCapacity = newCapacity;
}


/***************************************
 * Vector <T> :: RESIZE
 * This method will grow the current buffer
 * to newCapacity.
 **************************************/
template <class T>
void Vector <T> :: resize(int newCapacity) throw (const char *)
{
    
    // allocate the new array
    T * pNew;
    try
    {
        pNew = new T[newCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for Vector";
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
 * Vector <T> :: push_back
 * This method will add the element 't' to the
 * end of the current buffer.  
 **************************************/
template <class T>
void Vector <T> :: push_back (const T & t) throw (const char *)
{
      // grow if necessary
    if (numCapacity == 0)
        resize(1);
        else if (numElements == numCapacity)
            resize(numCapacity * 2);
            data[numElements++] = t;
}

/***************************************
 * Vector <T> :: assigment operator
 **************************************/
template <class T>
Vector <T> & Vector <T> :: operator = (const Vector <T> & rhs)
throw (const char *)
{
    if (&rhs == this)
        return *this;

    numElements = 0;
    
    if (rhs.numElements > numCapacity)
        resize(rhs.numElements);
    numElements = rhs.numElements;
        for (int i = 0; i < rhs.numElements; i++)
            data[i] = rhs.data[i];
            
            return *this;
}

#endif /* vector_h */
