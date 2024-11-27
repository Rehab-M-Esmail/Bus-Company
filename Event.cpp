//
// Created by Rehab Mahmoud on 10/12/2023.
//
#pragma once
#include "Company.h"
#include <iostream>
using namespace std;
#include "Event.h"
Leave::Leave(int ID,int startStation,Company* c)
{
    id=ID;
    StartStation= startStation;
}
void Leave:: Execute() {
Station* StationPTR;
StationPTR=c->returnStationPTR(StartStation);
StationPTR->RemovePassenger(id);
//Stations[stoi(EventData[3])].PassRemove(stoi(EventData[2]));
return;
/* Node<Passenger>* currentNode = linkedList.getHead();
 Node<Passenger>* prevNode = nullptr;

 while (currentNode != nullptr) {
     if (currentNode->getItem().getId() == passengerInfo.getId()) {
         if (prevNode == nullptr) {
             linkedList.SetHead(currentNode->getNext());
         }
         else {
             prevNode->setNext(currentNode->getNext());
         }

         delete currentNode;
         currentNode = nullptr;

         return;
     }
     prevNode = currentNode;
     currentNode = currentNode->getNext();
 }
 cout << "Passenger Not Found" << endl;*/
}
Event::Event(Time t)
{
    EventTime=t;
}
Event::Event()
{

}
 void Event:: Execute()
{

}
Time Event::GetEventTime()
{
    return EventTime;
}
Arrival::Arrival(string direction,string type,Time t,int ID,int start,int End,Company* c):
        direction(direction),type(type),Event(t),ID(ID),start(start),End(End){}

void Arrival::Execute()
{
    Passenger temp(direction,type,EventTime,ID,start,End);
    c().PassAddToStation(temp);
    //The event should have call the company to return a pointer to the start station
     //The station should have a function to add a passenger to the appropriate list
}