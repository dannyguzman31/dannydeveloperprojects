
/***********************************************************************
 * Header:
 *    QUEUE
 * Author
 *    Daniel Guzman
 * Summary:
 #    A queue is called a First-In-First-Out (FIFO) data 
 #    structure. It can equally be called Last-In-Last-Out 
 #   (LILO). A queue is an ordered collection of elements 
 #    where the client can remove elements from only one 
 #    end (the front) and add access to the other (the back)
 #    This will work exactly like the std::queue class.
 * Time: About 4-5 hours to do this assignment
 ************************************************************************/

#ifndef queue_h
#define queue_h

#include <iostream>

#include <cassert>
using namespace std;

template <class T>
class Queue
{
public:
    // constructors and destructors
    Queue() : numCapacity(0), numElements(0), data(NULL) {}
    Queue(int numCapacity)                 throw (const char *);
    Queue(const Queue & rhs)               throw (const char *);
    ~Queue()            { if (numCapacity) delete [] data; }
    Queue & operator = (const Queue & rhs) throw (const char *);
    
    // standard container interfaces
    int size()     const { return numElements;                }
    int capacity() const { return numCapacity;                }
    bool empty()   const { return numElements == 0;           }
    void clear()         { numElements = 0;                   }
    
    // Queue-specific interfaces
    void push(const T & t)                 throw (const char *);
    T & top()                              throw (const char *);
    T   top()      const                   throw (const char *);
    void pop()throw (const char *)
    {
        if(this->empty())
            throw "ERROR: Unable to pop from an empty Queue";
        else
            fIndex = ( fIndex +1) % capacity();
            numElements--;
    }
    
    T & front() throw(const char *);
    T & front() const throw(const char *);
    T & back() throw(const char *);
    T & back() const throw(const char *);
    
    // gets the index in queue
    int getfIndex()
    {
        return fIndex;
    }
    int getbIndex()
    {
        return bIndex;
    }

private:
    T * data;
    int numCapacity;
    int numElements;
    
    void resize(int newCapacity);
    int fIndex;
    int bIndex;
};

/**************************************************************************
 * Queue :: ASSIGNMENT
 **************************************************************************/
template <class T>
Queue <T> & Queue <T> :: operator = (const Queue <T> & rhs)
throw (const char *)
{
    /*
    try
    {
        if (this->numCapacity < rhs.numCapacity)
        {
            T * temp = new T[rhs.capacity()];
            delete [] data;
            data = temp;
        }
        numCapacity = rhs.capacity();
        numElements = rhs.size();
        fIndex = rhs.fIndex;
        bIndex = rhs.bIndex;
        
        
        for (int i = rhs.fIndex; i != rhs.bIndex; i = ((i + 1)% rhs.capacity()))
        {
            data[i] = rhs.data[i];
        }
      
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: Unable to a new buffer for Queue";
    }
    
    */
    if (rhs.size() > this->numCapacity)
        this->resize(rhs.size());
        
            for (int i = 0; i < this->numElements; i++)
            this->data[i] = rhs.data[i];
            
            this->numElements = rhs.size();
            
            return *this;
     
     
    return *this;
}

/****************************************************************************
 * Queue :: COPY CONSTRUCTOR
 ***************************************************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
    
    if (rhs.numCapacity == 0)
    {
        numCapacity = 0;
        numElements = 0;
        data = NULL;
        return;
    }
    try
    {
        this->data = new T[rhs.numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    numCapacity = rhs.numCapacity;
    numElements = rhs.numElements;
    
    for (int i = 0; i < numElements; i++)
        data[i] = rhs.data[i];
        
}

/******************************************************************************
 * Queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 *****************************************************************************/
template <class T>
Queue <T> :: Queue(int numCapacity) throw (const char *)
{
    
    if (numCapacity == 0)
    {
        
        numCapacity = 0;
        numElements = 0;
        data = NULL;
        return;
    }
    
    try
    {
        //T t;
        data = new T[numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    
    this->numCapacity = numCapacity;
    this->numElements = 0;
}

/****************************************************************************
 * Queue :: PUSH
 ***************************************************************************/
template <class T>
void Queue <T> :: push(const T & t) throw(const char *)
{
    try
    {
        if (numElements == numCapacity)
        {
            if (numElements)
                resize(2 * numCapacity);
                else
                    resize(1);
                    }
        
        data[numElements] = t;
        numElements++;
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for Queue";
    }
    
}

/***************************************************************************
 * Queue :: RESIZE
 **************************************************************************/
template <class T>
void Queue <T> :: resize(int newCapacity)
{
    
    T *new_data = new T[newCapacity];
    
    for (int i = 0; i < numElements; i++)
        new_data[i] = data[i] ;
    
    delete[] data;
    data = new_data;
    
    numCapacity = newCapacity ;
    
}

/***************************************************************************
 * Queue :: TOP
 ***************************************************************************/
template <class T>
T & Queue <T> ::       top() throw(const char *)
{
    if (!empty())
        return data[size() - 1];
    else
        throw "ERROR: Unable to reference the element from an empty Queue";
}

template <class T>
T   Queue <T> :: top() const throw(const char *)
{
    if (!empty())
        return data[size() - 1];
    else
        throw "ERROR: Unable to reference the element from an empty Queue";
}

/****************************************************************************
 * Queue :: FRONT
 *  Returns the item currently at the front 
 *  of the queue. This item is returned by-
 *  reference, so the last item can be changed 
 *  through the front() method. If the queue 
 *  is currently empty, an exception
 *  will be thrown:
 ERROR: attempting to access an item in an empty queue
 ****************************************************************************/
template <class T>
T & Queue<T>::front() throw(const char *)
{
    if (this->empty())
        throw "Error: attempting to access an iten in an empty queue";
    else
        return this->data[fIndex];
}

template <class T>
T & Queue<T>::front()const throw(const char *)
{
    if (this->empty())
        throw "Error: attempting to access an iten in an empty queue";
    else
        return this->data[fIndex];
}

/*****************************************************************************
 * Queue :: BACK
 *  Returns the item currently at the back of the queue. This item 
 *  is returned by-reference so, the last item can be changed through
 *  the back() method. If the queue is currently empty, an exception
 *  will be thrown:
 ERROR: attempting to access an item in an empty queue
 ****************************************************************************/
template <class T>
T & Queue<T>::back() throw (const char *)
{
    if(this->empty())
        throw "Error: attempting to acess an item in an empty queue";
    else
        return this->data[bIndex];
    
}

template <class T>
T & Queue<T>::back()const throw(const char *)
{
    if (this->empty())
        throw "Error: attempting to access an iten in an empty queue";
    else
        return this->data[bIndex];
}



#endif /* queue_h */
