//
// Created by Rehab Mahmoud on 10/12/2023.
//

#include "Bus.h"

Bus::Bus(int id, string type, int maxS, int duration, int aftertrips)
{
    NumOfPassengers = 0;
    NumOfJourneys = 0;
    NumOfTrips = 0;
    BusID = "B" + to_string(id);
    MaxCapacity = maxS;
    MaintainAfterTrips = aftertrips;
    BusyTime = 0;
    MaintainDuration = duration;
    BusType = type;
    CurrentStation = 0;
    NextStation = 1;
    BusDirection = "FWD";
    if (type == "MBus")
        MaxMbus = maxS;
    else if (type == "WBus")
        MaxWBus = maxS;
}

Bus::Bus(int id, string type, int duration, int aftertrips)
{
    NumOfPassengers = 0;
    NumOfJourneys = 0;
    NumOfTrips = 0;
    BusID = "B" + to_string(id);
    BusyTime = 0;
    MaintainDuration = duration;
    BusType = type;
    CurrentStation = 0;
    NextStation = 1;
    BusDirection = "FWD";
    if (type == "MBus")
        MaxCapacity = MaxMbus;
    else if (type == "WBus")
        MaxCapacity = MaxWBus;
}

bool Bus::BusIsFull()
{
    if (NumOfPassengers == MaxCapacity)
        return true;
    return false;
}

bool Bus::BusIsEmpty()
{
    if (NumOfPassengers == 0)
        return true;
    return false;
}

void Bus::SetMaxCapacity(int max)
{
    MaxCapacity = max;
}

int Bus::GetMaxCapacity()
{
    return MaxCapacity;
}

void Bus::SetBusID(string id)
{
    BusID = id;
}

string Bus::GetBusID()
{
    return BusID;
}

void Bus::SetBusyTime(int b)
{
    BusyTime = b;
}

int Bus::GetBusyTime()
{
    return BusyTime;
}

void Bus::SetMantainDur(int m)
{
  MaintainDuration=m;
}

Time Bus::GetMaintainDuration()
{
    return MaintainDuration;
}

void Bus::SetMaintainAfterTrips(int t)
{
    MaintainAfterTrips = t;
}

int Bus::GetMaintainAfterTrips()
{
    return MaintainAfterTrips;
}

void Bus::SetNumPassengers(int num)
{
    NumOfPassengers = num;
}

int Bus::GetNumPassengers()
{
    return NumOfPassengers;
}

void Bus::SetNumJourneys(int num)
{
    NumOfJourneys = num;
}

int Bus::GetNumJourneys()
{
    return NumOfJourneys;
}

void Bus::SetNumTrips(int num)
{
    NumOfTrips = num;
}

int Bus::GetNumTrips()
{
    return NumOfTrips;
}

void Bus::SetBusType(string type)
{
    BusType = type;
}

string Bus::GetBusType()
{
    return BusType;
}

void Bus::SetBusDirection(string Dir)
{
    BusDirection = Dir;
}

string Bus::GetBusDirection()
{
    return BusDirection;
}

void Bus::SetCurrentStation(int s)
{
    CurrentStation = s;
}

int Bus::GetCurrentStation()
{
    return CurrentStation;
}

void Bus::SetNextStation(int n)
{
    NextStation = n;
}

int Bus::GetNextStation()
{
    return NextStation;
}

Passenger* Bus::GetPassOff(int currentSt)
{
    Passenger x;
    PassengersOnBoard.peek(x);
    if (x.getEndStation() == currentSt) {
        Passenger passenger;
        PassengersOnBoard.dequeue(passenger);
        NumOfPassengers--;
        return &passenger;
    }
    return nullptr;

}

void Bus::GetPassOn(Passenger* passenger)
{
    PassengersOnBoard.enqueue(*passenger, passenger->getEndStation()-passenger->getStartStation());
    NumOfPassengers++;
}
void Bus::PrintBusInfo() {
    cout<<BusID<<"["<<BusDirection<<","<<BusType<<","<<MaxCapacity<<"]";
    Passenger temp;
    PriorityQueue<Passenger> tempQueue;
    cout<<"{";
    while(!PassengersOnBoard.isEmpty())
    {
        PassengersOnBoard.dequeue(temp);
        cout<<temp.getId()<<",";
        tempQueue.enqueue(temp,temp.getPriority());//Store the passengers till it prints all IDs
    }
    cout<<"}";
    tempQueue.dequeue(temp);
    PassengersOnBoard.enqueue(temp,temp.getPriority());
}
Time Bus::GeTArrialTime()
{
    return arrivalTime;
}