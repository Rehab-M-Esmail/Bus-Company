#pragma once
#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue {
protected:
    Node<T>* backPtr;
    Node<T>* frontPtr;
    int Count;
    int MaxSize;
public:
    LinkedQueue();
    bool isEmpty() const;
    bool isFull() const;
    bool enqueue(const T& newEntry);
    bool dequeue(T& frntEntry);
    bool peek(T& frntEntry)  const;
    ~LinkedQueue();
    void SetCount(int c);
    int GetCount() const;
    void PrintQueue();
    void SetMaxSize(int s);
    int GetMaxSize() const;


    void SetBackPtr(Node<T>* p);
    Node<T>* GetBackPtr() const;


    void SetFrontPtr(Node<T>* p);
    Node<T>* GetFrontPtr() const;
};

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
    backPtr = nullptr;
    frontPtr = nullptr;
    Count = 0;
    MaxSize = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////



template <typename T>
void LinkedQueue<T>::SetCount(int c) {
    Count = c;
}

template <typename T>
int LinkedQueue<T>::GetCount() const {
    return Count;
}


template <typename T>
int LinkedQueue<T>::GetMaxSize() const {
    return MaxSize;
}

template <typename T>
void LinkedQueue<T>::SetMaxSize(int s) {
    MaxSize = s;
}

//
template <typename T>
bool LinkedQueue<T>::isFull() const {
    if (Count == MaxSize)
        return true;
    return false;
}

template <typename T>
void LinkedQueue<T>::SetBackPtr(Node<T>* p) {
    backPtr = p;
}

template <typename T>
Node<T>* LinkedQueue<T>::GetBackPtr() const {
    return backPtr;
}

template <typename T>
void LinkedQueue<T>::SetFrontPtr(Node<T>* p) {
    frontPtr = p;
}

template <typename T>
Node<T>* LinkedQueue<T>::GetFrontPtr() const {
    return frontPtr;
}

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
    Node<T>* newNodePtr = new Node<T>(newEntry);
    // Insert the new node
    if (isEmpty())	//special case if this is the first node to insert
        frontPtr = newNodePtr; // The queue is empty
    else
        backPtr->setNext(newNodePtr); // The queue was not empty

    backPtr = newNodePtr; // New node is the last node now
    return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
    if (isEmpty())
        return false;

    Node<T>* nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();
    // Queue is not empty; remove front
    if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
        backPtr = nullptr;

    // Free memory reserved for the dequeued node
    delete nodeToDeletePtr;

    return true;
}


/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
//
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
    if (isEmpty())
        return false;

    frntEntry = frontPtr->getItem();
    return true;

}

template <typename T>
void PrintQueue()
{
    T K;
    cout<<"\nQueue contents: ";
    while(dequeue(K))
        cout << K << " ";
    cout<<endl;
}


///////////////////////////////////////////////////////////////////////////////////
//
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    //Note that the cout statements here is just for learning purpose
    //They should be normally removed from the destructor
    cout << "\nStarting LinkedQueue destructor...";
    cout << "\nFreeing all nodes in the queue...";

    //Free all nodes in the queue
    T temp;
    while (dequeue(temp));

    cout << "\n Is LinkedQueue Empty now?? ==> " << boolalpha << isEmpty();
    cout << "\nEnding LinkedQueue destructor..." << endl;
}

#endif
