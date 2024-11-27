//
// Created by Rehab Mahmoud on 01/01/2024.
//

#include "Queue.h"
#include <iostream>
#include "Passenger.h"

using namespace std;

template <typename T>
class PriorityQueue :public LinkedQueue<T> {
public:
    bool enqueue(const T& newEntry, int priority);
    void Print();
    void printPassengers();
};

template<typename T>
inline bool PriorityQueue<T>::enqueue(const T& newEntry, int priority) {
    Node<T>* newNode = new Node<T>(newEntry, priority);
    if (this->isEmpty()) {
        this->SetFrontPtr(newNode);
        this->SetBackPtr(newNode);
    }

    else {
        Node<T>* tempH = this->GetFrontPtr();
        Node<T>* prevNode = nullptr;
        while (tempH != nullptr && tempH->GetPriority() <= priority) {
            prevNode = tempH;
            tempH = tempH->getNext();
        }
        if (prevNode == nullptr) {
            newNode->setNext(this->GetFrontPtr());
            this->SetFrontPtr(newNode);
        }
        else {
            prevNode->setNext(newNode);
            newNode->setNext(tempH);
            if (tempH == nullptr)
                this->SetBackPtr(newNode);
        }
    }
    this->SetCount(this->GetCount() + 1);
    return true;
}

template<typename T>
void PriorityQueue<T>::Print() {
    Node<T>* tempPtr = this->GetFrontPtr();
    while (tempPtr != nullptr) {
        cout << tempPtr->getItem() << endl;
        tempPtr = tempPtr->getNext();
    }
}
/*
void PriorityQueue<Passenger>::printPassengers()
{
    for(int i=0;i<Count;i++)
    {
        Passenger temp;
        temp.printInfo();
    }
}*/
