#include <iostream>
#include "Company.h"
#include "PriorityQueue.h"
#include <string.h>
#include "Passenger.h"
class Passenger;
using namespace std;
class Bus {
private:
    string BusID;
    string BusType;
    string BusDirection;
    int NumOfPassengers;
    int MaxCapacity;
    int MaxMbus;
    int MaxWBus;
    int BusyTime;
    Time MaintainDuration;
    int MaintainAfterTrips;
    int NumOfJourneys;
    int NumOfTrips;
    int CurrentStation;
    int NextStation;
    Time MoveTime;
    Time arrivalTime;
    PriorityQueue<Passenger> PassengersOnBoard;

public:
    Bus() {};
    Bus(int id, string type, int maxS, int duration, int aftertrips);
    Bus(int id, string type, int duration, int aftertrips);

    bool BusIsFull();
    bool BusIsEmpty();
    Time GeTArrialTime();

    void SetMaxCapacity(int max);
    int GetMaxCapacity();

    void SetBusID(string id);
    string GetBusID();

    void SetBusyTime(int b);
    int GetBusyTime();

    void SetMantainDur(int m);
    int GetMaintainDuration();

    void SetMaintainAfterTrips(int t);
    int GetMaintainAfterTrips();

    void SetNumPassengers(int num);
    int GetNumPassengers();

    void SetNumJourneys(int num);
    int GetNumJourneys();

    void SetNumTrips(int num);
    int GetNumTrips();

    void SetBusType(string type);
    string GetBusType();

    void SetBusDirection(string Dir);
    string GetBusDirection();

    void SetCurrentStation(int s);
    int GetCurrentStation();
    Time GetMoveTime();

    void SetNextStation(int n);
    int GetNextStation();

    Passenger* GetPassOff(int CurrentStation);
    //peek bec priority according to station return passenger or null
    void GetPassOn(Passenger* passenger);


    void PrintBusInfo() ;
    //busycounter in minutes +=loadstart-emptytime. check the function if the list was empty,increment the counter
    //Time loadstart,emptytime(last passenger who get off).
};

