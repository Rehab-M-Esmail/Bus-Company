#pragma once
#include "Passenger.h"
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Time.h"
#include "Station.h"
#include "Event.h"
class Company;
#ifndef Company_H
#define Company_H
using namespace std;
Company c();
//divide the files to headers and cpps
//event.cpp include company.cpp

class Event {
protected:
    Time EventTime;
public:
    virtual void Execute() = 0;
    Event(Time t);
    Time GetEventTime();
    Event();
};

class Arrival : public Event {
private:
    string direction;
    string type;
    int ID;
    int start;
    int End;
public:
    Arrival(string direction,string type,Time t,int ID,int start,int End,Company* c);
    void Execute() override;

};

class Leave : public Event {
private:
    int id;
    int StartStation;

public:
    Leave(int ID,int startStation,Company* c);
    void Execute()override;
};
#endif //Company_H
