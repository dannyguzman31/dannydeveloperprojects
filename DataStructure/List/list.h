/***********************************************************************
 * Implementation:
 *    LIST
 * Summary:
 *
 * Author
 *    Daniel Guzman
 **********************************************************************/

#ifndef list_h
#define list_h
#include "node.h"


template <class T>
class List
{
public:
    //constructors and destructor
    List() : pHead(NULL), pTail(NULL), numElements(0){};
    List(const List<T> &rhs) throw(const char *) : pHead(NULL), pTail(NULL), numElements(0)
    {
        try
        {
            *this = rhs;
        }
        catch (...)
        {
            throw "ERROR: unable to allocate a new node for a List";
        }
    }
    ~List(){clear();}
    
    // assignment operator
    List<T> &operator = (const List<T> &rhs);
    
    // standard container interfaces
    int  size() const { return numElements;}
    bool empty() const { return pHead == NULL;}
    void clear() {freeData(pHead);}
    
    // the various ListIterator interfaces
    class ListIterator;
    class const_ListIterator;
    class reverse_ListIterator;
    class const_reverse_ListIterator;
    ListIterator begin() { return ListIterator(pHead); }
    ListIterator end() { return ListIterator(NULL); }
    reverse_ListIterator rbegin() { return reverse_ListIterator(pTail); }
    reverse_ListIterator rend() { return reverse_ListIterator(NULL); }
    const_ListIterator cbegin() const { return const_ListIterator(pHead);}
    const_ListIterator cend() const { return const_ListIterator(NULL);}
    const_reverse_ListIterator crbegin() const { return const_reverse_ListIterator(pTail);}
    const_reverse_ListIterator crend() const { return const_reverse_ListIterator(NULL);}
    
    // pushes and pops
    void push_back(const T &data);
    void push_front(const T &data) throw(const char *);
    void pop_back(){erase(pTail);}
    void pop_front(){erase(pHead);}
    
    // data reference to first node in the List
    T &front() throw(const char *)
    {
        if (!empty())
            return pHead->data;
        else
            throw "ERROR: unable to access data from an empty List";
    }
    // data reference to last node in List
    T &back() throw(const char *)
    {
        if (!empty())
            return pTail->data;
        else
            throw "ERROR: unable to access data from an empty List";
    }
    
    // cleans up all data in the List
    void freeData(Node<T> *&pHead)
    {
        if (pHead == NULL)
            return;
        freeData(pHead->pNext);
        delete pHead;
        pHead = pTail = NULL;
        numElements = 0;
    }
    
    //erase and insert
    void erase(ListIterator & it) throw (const char *);
    void insert(ListIterator & it, const T & data) throw (const char *);
    
private:
    Node<T> *pHead;
    Node<T> *pTail;
    int numElements;
};

/***************************************
 * List <T> :: assigment operator
 * This operator will copy the contents of the
 * rhs onto *this, growing the buffer as needed
 *     INPUT  : rhs the set to copy from
 *     OUTPUT : *this
 **************************************/
template <class T>
List <T> & List <T> :: operator = (const List<T> &rhs)
{
    clear();
    for (Node<T> *p = rhs.pHead; p; p = p->pNext) {
        push_back(p->data);
    }
    return *this;
}

/*************************************************
 * List :: push_back
 * adds an element to the back of the List
 ***********************************************/
template <class T>
void List<T> :: push_back(const T &data)
{
    try
    {
        Node<T> *pNew = new Node<T>(data);
        pNew->pPrev = pTail;
        if (pTail != NULL)
            pTail->pNext = pNew;
        else
            pHead = pNew;
        pTail = pNew;
        numElements++;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a List";
    }
}

/*************************************************
 * List :: push_front
 * adds an element to the front of the List
 ***********************************************/
template <class T>
void List<T> :: push_front(const T &data) throw(const char *)
{
    try
    {
        Node<T> *pNew = new Node<T>(data);
        pNew->pNext = pHead;
        if (pHead != NULL)
            pHead->pPrev = pNew;
            else
                pTail = pNew;
                pHead = pNew;
                numElements++;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a List";
    }
}

/*************************************************
 * List :: insert
 * Uses ListIterator to position insert of new node
 ***********************************************/
template <class T>
void List<T> :: insert(ListIterator & it, const T & data) throw (const char *)
{
    try
    {
        Node <T> * pNew = new Node <T> (data);
        if(it != NULL)
        {
            pNew->pNext = it;
            pNew->pPrev = it->pPrev;
            it->pPrev = pNew;
            if(pNew->pPrev)
                pNew->pPrev->pNext == pNew;
                }
        return pNew;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a List";
    }
    
}

/*************************************************
 * List :: erase
 * Uses ListIterator to position insert of new node
 ***********************************************/
template <class T>
void List<T> :: erase(ListIterator & it) throw (const char *)
{
    if (empty())
        return;
    
    try
    {
        Node <T> * p;
        p = pHead;
        if(p->data == *it)
            delete p;
        else
            p = p->pNext;
            
            numElements--;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a List";
    }
    
}

/**************************************************
 * List ListIterator
 * An ListIterator through List
 *************************************************/
template <class T>
class List <T> :: ListIterator
{
public:
    //constructors
    ListIterator() : p(NULL){};
    ListIterator(Node<T> * p) : p(p){};
    ListIterator(const ListIterator & rhs) { *this = rhs; }
    
    //assignment operator
    ListIterator & operator = (const ListIterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    // equals operator overload
    bool operator == (const ListIterator & it) const
    {
        return (it.p == this->p);
    }
    
    // not equals operator overload
    bool operator != (const ListIterator & it) const
    {
        return it.p != this->p;
    }
    
    // prefix increment operator overload
    ListIterator & operator ++ ()
    {
        p=p->pNext;
        return *this;
    }
    
    // prefix decrement operator overload
    ListIterator & operator -- ()
    {
        p = p->pPrev;
        return *this;
    }
    
    // postfix increment operator overload
    ListIterator operator++(int postfix)
    {
        ListIterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    // postfix decrement operator overload
    ListIterator operator--(int postfix)
    {
        ListIterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    
    // dereference operator operator overload
    T & operator * () throw (const char *)
    {
        if(p)
            return p->data;
        else
            throw "ERROR: Trying to dereference a NULL pointer";
    }
    
private:
    Node <T> * p;
};

/**************************************************
 * List REVERSE_ListIterator
 * An ListIterator through List backwards
 *************************************************/
template <class T>
class reverse_ListIterator
{
public:
    // default constructor
    reverse_ListIterator() : p(NULL) {};
    
    // initialize to direct p to some item
    reverse_ListIterator(Node<T> * p) : p(p) {};
    
    // copy constructor
    reverse_ListIterator(const reverse_ListIterator & rhs) { *this = rhs; }
    
    // assignment operator overload
    reverse_ListIterator & operator = (const reverse_ListIterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    // not equals operator overload
    bool operator != (const reverse_ListIterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // equals operator overload
    bool operator == (const reverse_ListIterator & rhs) const
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
    reverse_ListIterator & operator ++ ()
    {
        p=p->pPrev;
        return *this;
    }
    
    // prefix decrement operator overload
    reverse_ListIterator & operator -- ()
    {
        p = p->pNext;
        return *this;
    }
    
    // postfix increment operator overload
    reverse_ListIterator operator++(int postfix)
    {
        reverse_ListIterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    // postfix decrement operator overload
    reverse_ListIterator operator--(int postfix)
    {
        reverse_ListIterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    
private:
    Node <T> * p;
};

/**************************************************
 * List CONST ListIterator
 * An ListIterator through List
 *************************************************/
template <class T>
class List <T> :: const_ListIterator
{
public:
    // default constructor
    const_ListIterator() : p(NULL) {}
    
    // initialize to direct p to some item
    const_ListIterator(const Node<T> * p) : p(p) {}
    
    // copy constructor
    const_ListIterator(const const_ListIterator & rhs) { *this = rhs; }
    
    // assignment operator
    const_ListIterator & operator = (const const_ListIterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    // not equals operator overload
    bool operator != (const const_ListIterator & rhs) const
    {
        return rhs.p != this->p;
    }
    // equals operator overload
    bool operator == (const const_ListIterator & rhs) const
    {
        return (rhs.p == this->p);
    }
    
    // dereference operator overload
    T operator * () const
    {
        return p->data;
    }
    
    // prefix increment operator overload
    const_ListIterator & operator ++ ()
    {
        p=p->pNext;
        return *this;
    }
    
    // prefix decrement operator overload
    const_ListIterator & operator -- ()
    {
        p = p->pPrev;
        return *this;
    }
    
    // postfix increment operator overload
    const_ListIterator operator++(int postfix)
    {
        const_ListIterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    // postfix decrement operator overload
    const_ListIterator operator--(int postfix)
    {
        const_ListIterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    
private:
    const Node<T> * p;
};

/**************************************************
 * List CONST REVERSE ListIterator
 * An ListIterator through List
 *************************************************/
template <class T>
class List <T> :: const_reverse_ListIterator
{
public:
    // default constructor
    const_reverse_ListIterator() : p(NULL) {}
    
    // initialize to direct p to some item
    const_reverse_ListIterator(const Node<T> * p) : p(p) {}
    
    // copy constructor
    const_reverse_ListIterator(const const_reverse_ListIterator & rhs) { *this = rhs; }
    
    // assignment operator
    const_reverse_ListIterator & operator = (const const_reverse_ListIterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    // not equals operator overload
    bool operator != (const const_reverse_ListIterator & rhs) const
    {
        return rhs.p != this->p;
    }
    // equals operator overload
    bool operator == (const const_reverse_ListIterator & rhs) const
    {
        return (rhs.p == this->p);
    }
    
    // dereference operator overload
    T operator * () const
    {
        return p->data;
    }
    
    // prefix increment operator overload
    const_reverse_ListIterator & operator ++ ()
    {
        p=p->pPrev;
        return *this;
    }
    
    // prefix decrement operator overload
    const_reverse_ListIterator & operator -- ()
    {
        p = p->pNext;
        return *this;
    }
    
    // postfix increment operator overload
    const_reverse_ListIterator operator++(int postfix)
    {
        const_reverse_ListIterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    // postfix decrement operator overload
    const_reverse_ListIterator operator--(int postfix)
    {
        const_reverse_ListIterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    
private:
    const Node<T> * p;
};


#endif /* list_h */
