#pragma once
#include "Queue.h"
#include "Bus.h"
#include "Passenger.h"
#include "DerivedQueue.h"
#include "Station.h"
#include "PriorityQueue.h"
#include "Company.h"

class Station {
private:
    int StationNumber;
    int NumofStations;
    Company *com;

    PriorityQueue<Passenger> SPWaitingFWD;
    PriorityQueue<Passenger> SPWaitingBCK;

    LinkedQueue <Passenger> WPWaitingFWD;
    LinkedQueue <Passenger> WPWaitingBCK;

    DerivedQueue NPWaitingFWD;
    DerivedQueue NPWaitingBCK;

    LinkedQueue <Bus> WaitingFWDBuses;
    LinkedQueue <Bus> WaitingBCKBuses;

public:

    Station();

     void printStatus(); //Rehab
    int GetStaionNum();
    void printPassengers();
    void BusLeave(Company P);

    void SetStaionNum(int num);

    int GetNumofStations();

    void SetNumofStations(int num);

    float CalculateAVGwaitingTime() ;
//Prioirity:
//SP: aged->1 POD->2 pregnant->3
//WP:4
//NP:5

    void PassAdd(Passenger *passenger);

    void RemovePassenger(int ID);

    void PassPromote();

    void BusAdd(Bus *bus);
    void BusBoarding(Company* C, Time T);
    void BusOffBoarding(Company* c );
    void ExecuteoneMinute(Company c,Time currentTime);
    bool waitingPassengers();
    void BoardingWPForOneMinute();
    void BoardingNPForOneMinute();
    void BoardingSPForOneMinute();

};