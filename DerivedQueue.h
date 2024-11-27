//
// Created by Rehab Mahmoud on 01/01/2024.
//
#pragma once
#ifndef DSPROJECT_DERIVEDQUEUE_H
#define DSPROJECT_DERIVEDQUEUE_H


#include "Queue.h"
#include "Passenger.h"


class DerivedQueue: public LinkedQueue<Passenger> {
public:
   // return then dequeue
    Node<Passenger>* dequeue(int id) {
        if (isEmpty()) {
            return nullptr;
        }

        Node<Passenger>* tempHead = this->GetFrontPtr();
        Node<Passenger>* prevNode = nullptr;
        int found = 0;

        while (tempHead != nullptr) {
            if (tempHead->getItem().getId() == id) {
                found = 1;
                break;
            }
            prevNode = tempHead;
            tempHead = tempHead->getNext();
        }

        if (found == 1) {
            if (prevNode == nullptr) {
                this->SetFrontPtr(tempHead->getNext());
            } else {
                prevNode->setNext(tempHead->getNext());
            }
            Count--;
            return tempHead;
        }
        else {
            cout << "ID not found" << endl;
            return nullptr;
        }
    }

    void Print() {
        Node<Passenger>* tempPtr = this->GetFrontPtr();
        while (tempPtr != nullptr)
        {
            cout<<tempPtr->getItem().printInfo();
            tempPtr = tempPtr->getNext();
        }
    }
    Node<Passenger>* SearchforPassenger(int ID)
    {
        Node<Passenger>* temp= this->GetFrontPtr();
        while(temp->getItem().getId()!=ID)
        {
            temp=temp->getNext();
        }
        return temp;//                                   ??
    }

    ~DerivedQueue()
    {
        //Note that the cout statements here is just for learning purpose
        //They should be normally removed from the destructor
        //cout << "\nStarting DerivedQueue destructor...";
        //cout << "\nFreeing all nodes in the queue...";

        //Free all nodes in the queue

        Passenger P;
        while (dequeue(P.getId()));

        //cout << "\n Is DerivedQueue Empty now?? ==> " << boolalpha << isEmpty();
        //cout << "\nEnding DerivedQueue destructor..." << endl;
    }


};



#endif //DSPROJECT_DERIVEDQUEUE_H
