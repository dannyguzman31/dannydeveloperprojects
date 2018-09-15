
/***********************************************************************
 * Header:
 *    STACK
 * Author
 *    Daniel Guzman
 * Summary:
 *    creates a class encapsulating the notion of
 *    a stack. This will work exactly like the std::stack class.
 * Time: About 4-5 hours to do this assignment
 ************************************************************************/
#ifndef stack_h
#define stack_h
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template <class T>
class Stack
{
public:
    // constructors and destructors
    Stack() : numCapacity(0), numElements(0), data(NULL) {}
    Stack(int numCapacity)                 throw (const char *);
    Stack(const Stack & rhs)               throw (const char *);
    ~Stack()            { if (numCapacity) delete [] data; }
    Stack & operator = (const Stack & rhs) throw (const char *);
    
    // standard container interfaces
    int size()     const { return numElements;                }
    int capacity() const { return numCapacity;                }
    bool empty()   const { return numElements == 0;           }
    void clear()         { numElements = 0;                   }
    
    // Stack-specific interfaces
    void push(const T & t)                 throw (const char *);
    T & top()                              throw (const char *);
    T   top()      const                   throw (const char *);
    void pop()throw (const char *)
    {
        if(this->empty())
            throw "ERROR: Unable to pop from an empty Stack";
        else
            numElements--;
    }
  
private:
    T * data;
    int numCapacity;
    int numElements;
    
    void resize(int newCapacity);
};

/*******************************************
 * Stack :: ASSIGNMENT
 *******************************************/
template <class T>
Stack <T> & Stack <T> :: operator = (const Stack <T> & rhs)
throw (const char *)
{
    if (rhs.size() > this->numCapacity)
        this->resize(rhs.size());
        
        assert(this->numCapacity >= rhs.numElements);
        
        for (int i = 0; i < this->numElements; i++)
            this->data[i] = rhs.data[i];
            
            this->numElements = rhs.size();
            
            return *this;
}

/*******************************************
 * Stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
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

/**********************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int numCapacity) throw (const char *)
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
        T t;
        data = new T[numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }

    this->numCapacity = numCapacity;
    this->numElements = 0;
}

/*******************************************
 * Stack :: PUSH
 *******************************************/
template <class T>
void Stack <T> :: push(const T & t) throw(const char *)
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
        throw "ERROR: Unable to allocate a new buffer for Stack";
    }
    
}

/*******************************************
 * Stack :: RESIZE
 *******************************************/
template <class T>
void Stack <T> :: resize(int newCapacity)
{
    
    T *new_data = new T[newCapacity];
    
    for (int i = 0; i < numElements; i++)
        new_data[i] = data[i];
    
    delete[] data;
    data = new_data;
    
    numCapacity = newCapacity;
    
}

/*******************************************
 * Stack :: TOP
 *******************************************/
template <class T>
T & Stack <T> ::       top() throw(const char *)
{
    if (!empty())
        return data[size() - 1];
    else
        throw "ERROR: Unable to reference the element from an empty Stack";
}

template <class T>
T   Stack <T> :: top() const throw(const char *)
{
    if (!empty())
        return data[size() - 1];
    else
        throw "ERROR: Unable to reference the element from an empty Stack";
}


/*

template <class T>
void Stack<T>::pop() throw (const char *)
{
    if(this->empty())
        throw "ERROR: Unable to pop from an empty Stack";
    else
        numElements--;
};
*/
#endif /* stack_h */
