#pragma once
#include "Node.h"
template<class T>
class LinkedList {
private:
    Node<T>* head;
    int count;
public:
    LinkedList() {
        head = nullptr;
    }
    Node<T>* GetNodePosition(int position) {
        Node<T>* tempHead = head;
        for (int i = 0; i < position - 1; i++) {
            tempHead = tempHead->getNext();
        }
        return tempHead;
    }

    void InsertNode(T val, int position) {
        Node<T>* newNode = new Node(val);

        if (position == 1) {
            newNode->setNext(head);
            head = newNode;
            count ++ ;
        }
        else {

            Node<T>* PrevNode = GetNodePosition(position - 1);
            if (PrevNode != nullptr) {
                if (PrevNode->getNext()== nullptr) {
                    PrevNode->setNext(newNode);
                }
            }
            else {
                newNode->setNext(PrevNode->getNext());
                PrevNode->setNext(newNode);
            }
            count++;
        }
    }
    void RemoveNode(Node<T> N, int position) {
        if (position == 1) {
            Node<T>* temphead = head;
            head = temphead->getNext();
            delete temphead;
            temphead = nullptr;
            count--;
        }
        else {
            Node<T>* temphead = GetNodePosition(position);
            Node<T>* PrevNode = GetNodePosition(position - 1);
            PrevNode->setNext(GetNodePosition(position + 1));
            delete temphead;
            temphead = nullptr;
            count--;
        }
    }

    void setCount(int counter)
    {
        count=counter;
    }
    int getCount()
    {
        return count;
    }
    Node<T>* getHead() {
        return head;
    }
    void SetHead(Node<T>* h) {
        head = h;
    }

};
