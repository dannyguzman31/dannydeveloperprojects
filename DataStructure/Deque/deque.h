/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    A deque is a double-ended queue. In other words, it is a
 *    combination of a queue and a stack. The deque will work
 *    exactly like the std::deque class.
 * Author:
 *    Daniel Guzman
 ***********************************************************************/

#ifndef deque_h
#define deque_h
#include <cassert>

/*************************************************************************
 * DEQUE
 ************************************************************************/
template <class T>
class Deque
{
public:
    // constructors and destructors
    Deque() : data(NULL), numCapacity(0), iFront(0), iBack(-1){}
    Deque(int numCapacity) throw (const char *);
    Deque(const Deque <T> & rhs) throw (const char *);
    Deque <T> & operator = (const Deque <T> & rhs) throw (const char *);
    ~Deque();
    
    // standard container interfaces
    
    int  size() const { return iBack - iFront + 1;}
    bool empty() const { return size() == 0;}
    int capacity() const { return numCapacity; }
    void clear()
    {
        iFront = 0;
        iBack = -1;
    }
    
    // Deque-specific interfaces
    
    void push_back(const T & t) throw (const char *);
    void push_front(const T & t) throw (const char *);
    void pop_back()throw (const char *);
    void pop_front() throw (const char *);
    T &front() throw(const char*);
    const T &front() const throw(const char*);
    T &back() throw(const char*);
    const T &back() const throw(const char*);
    
private:
    int iFront;
    int iBack;
    T *  data;
    int  numCapacity;
    void resize(int newCapacity) throw (const char *);
    const int normalized(int value) const;
    const int iFrontNormalized() const;
    const int iBackNormalized() const;
};

/*************************************************************************
 * DESTRUCTOR
 * When finished, the class should delete all the allocated memory
 ************************************************************************/
template <class T>
Deque <T> :: ~Deque()
{
    if (size() != 0)
        delete [] data;
}
/*************************************************************************
 * NON-DEFAULT constructors
 * non-default constructor: set the capacity initially
 ************************************************************************/
template <class T>
Deque <T> :: Deque(int numCapacity) throw (const char *) : iFront(0), iBack(-1)
{
    assert(numCapacity >= 0);
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
/*************************************************************************
 * COPY CONSTRUCTOR
 ************************************************************************/
template <class T>
Deque <T> :: Deque (const Deque <T> & rhs) throw (const char *) : numCapacity(0), data(0), iFront(0), iBack(-1)
{
    *this = rhs;
    
}
/*************************************************************************
 * Deque <T> :: RESIZE
 * This method will grow the current buffer to newCapacity.  It will
 * also copy all the data from the old buffer into the new.
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 *     THROW  : ERROR: Unable to allocate a new buffer for Deque
 ************************************************************************/
template <class T>
void Deque <T> :: resize(int newCapacity) throw (const char *)
{
    assert(numCapacity >= size());
    assert(numCapacity <= newCapacity);
    T *pNew;
    try
    {
        pNew = new T[newCapacity];
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for deque";
    }
    
    int j = 0;
    for(int i = iFront; i <= iBack; i++)
        pNew[j++] = data[normalized(i)];
        
        if(!empty())
            delete [] data;
    
    data = pNew;
    iFront = 0;
    iBack = j - 1;
    numCapacity = newCapacity;
    
}

/*************************************************************************
 * Deque <T> :: push_back
 * This method will add the element 't' to the end of the current buffer.
 * It will also grow the buffer as needed to accomodate the new element
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 *     THROW  : ERROR: Unable to allocate a new buffer for Deque
 ************************************************************************/
template <class T>
void Deque <T> :: push_back (const T & t) throw (const char *)
{
    assert(capacity() >= 0);
    assert(capacity() >= size());
    try
    {
        if (size() == capacity())
        {
            if(numCapacity == 0)
                resize(1);
                else
                    resize(capacity() * 2);
                    }
        iBack++;
        data[iBackNormalized()] = t;
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for deque";
    }
}
/*************************************************************************
 * Deque <T> :: push_front
 * This method will add the element 't' to the front of the current buffer.
 * It will also grow the buffer as needed to accomodate the new element
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 *     THROW  : ERROR: Unable to allocate a new buffer for Deque
 ************************************************************************/
template <class T>
void Deque <T> :: push_front (const T & t) throw (const char *)
{
    assert(capacity() >= 0);
    assert(capacity() >= size());
    try
    {
        if (size() == capacity())
        {
            if(numCapacity == 0)
                resize(1);
                else
                    resize(capacity() * 2);
                    }
        iFront--;
        data[iFrontNormalized()] = t;
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for deque";
    }
}
/*************************************************************************
 * Deque <T> :: pop_back
 * Removes an item from the back of the deque, serving to reduce the size
 * by one. If the deque is already empty, a exception will be thrown.
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 *     THROW  : Error: unable to pop from the back of empty deque
 ************************************************************************/
template <class T>
void Deque <T> :: pop_back()throw (const char *)
{
    if(!empty())
    {
        iBack--;
    }
    else
        throw "ERROR: unable to pop from the back of empty deque";
    
}

/*************************************************************************
 * Deque <T> :: pop_back
 * Removes an item from the front of the deque If the deque is already
 * empty, a exception will be thrown.
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 *     THROW  : Error: unable to pop from the back of empty deque
 ************************************************************************/
template <class T>
void Deque <T> :: pop_front()throw (const char *)
{
    if(!empty())
    {
        iFront++;
    }
    else
        throw "ERROR: unable to pop from the front of empty deque";
}
/*************************************************************************
 * Deque   <T> :: assigment operator
 * This operator will copy the contents of the rhs onto *this, growing
 * the buffer as needed
 *     INPUT  : rhs the Deque to copy from
 *     OUTPUT : *this
 *     THROW  : "ERROR: Unable to allocate a new buffer for Deque
 ************************************************************************/
template <class T>
Deque <T> & Deque <T> :: operator = (const Deque <T> & rhs) throw (const char *)
{
    assert(rhs.size() <= rhs.numCapacity);
    clear();
    
    if(rhs.size() > numCapacity)
        resize(rhs.numCapacity);
        
        for(int i = rhs.iFront; i <= rhs.iBack; i++)
            push_back(rhs.data[normalized(i)]);
            
            return *this;
}
/*************************************************************************
 * Deque <T> :: front
 * This method will return the item currently at the front of the Deque.
 * This item is returned by-reference, so the last item can be changed
 * through the front() method.
 *      INPUT :
 *      OUTPUT:
 *      THROW: ERROR: attempting to access an item in an empty Deque
 ************************************************************************/
//return by reference
template <class T>
T & Deque <T> :: front() throw(const char*)
{
    if (empty())
        throw "ERROR: unable to access data from an empty deque";
    else
        return data[iFrontNormalized()];
}

/*************************************************************************
 * Deque <T> :: front
 * This method will return the item currently at the front of the Deque.
 * This item is returned by-reference, so the last item can be changed
 * through the front() method.
 *      INPUT :
 *      OUTPUT:
 *      THROW: ERROR: attempting to access an item in an empty Deque
 ************************************************************************/
template <class T>
const T & Deque <T> :: front() const throw(const char*)
{
    if(empty())
        throw "ERROR: unable to access data from an empty deque";
    else
        return data[iFrontNormalized()];
}

/*************************************************************************
 * Deque <T> :: back
 * This method will return the item currently at the back of the Deque.
 * This item is returned by-reference so, the last item can be changed
 * through the back() method.
 *      INPUT :
 *      OUTPUT:
 *      THROW: ERROR: attempting to access an item in an empty Deque
 ************************************************************************/
template <class T>
T& Deque <T> :: back() throw(const char*)
{
    if(empty())
        throw "ERROR: unable to access data from an empty deque";
    else
        return data[iBackNormalized()];
}

/*************************************************************************
 * Deque <T> :: back
 * This method will return the item currently at the back of the Deque.
 * This item is returned by-reference so, the last item can be changed
 * through the back() method.
 *      INPUT :
 *      OUTPUT:
 *      THROW: ERROR: attempting to access an item in an empty Deque
 ************************************************************************/
template <class T>
const T& Deque <T> :: back() const throw(const char*)
{
    if(empty())
        throw "ERROR: unable to access data from an empty deque";
    else
        return data[iBackNormalized()];
}

/*************************************************************************
 * Deque <T> :: normalized
 * Checks if numcapacity is less than 0, then returns its value by
 * normalizing it.
 ************************************************************************/
 template <class T>
 const int Deque <T> :: normalized(int value) const
 {
 if(value % numCapacity < 0)
 return (numCapacity + (value % numCapacity));
 else
 return value % numCapacity;
 }
 /*************************************************************************
 * Deque <T> :: iFrontNormalized
 * Returns iFront normalized.
 ************************************************************************/
 template <class T>
 const int Deque<T> :: iFrontNormalized() const
 {
 return normalized(iFront);
 
 }
 /*************************************************************************
 * Deque <T> :: iBackNormalized
 * Returns iBack Normalized
 ************************************************************************/
 template <class T>
 const int Deque <T> :: iBackNormalized() const
 {
 return normalized(iBack);
 }

#endif /* deque_h */
