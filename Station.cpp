//
// Created by Rehab Mahmoud on 10/12/2023.
//
#include "Station.h"
#include "Company.h"

int Station::GetStaionNum()
{
    return StationNumber;
}
//Rehab
void Station::printPassengers()
{
    SPWaitingFWD.printPassengers();
    SPWaitingBCK.printPassengers();
    WPWaitingFWD.PrintQueue();
    WPWaitingBCK.PrintQueue();
    NPWaitingFWD.Print();
    NPWaitingBCK.Print();
}
//Rehab
void Station::printStatus()
{
printPassengers();
cout<<WaitingBCKBuses.GetCount()+WaitingFWDBuses.GetCount();
Bus temp;
LinkedQueue<Bus> tempQueue;
    while (!WaitingFWDBuses.isEmpty())
    {
        WaitingFWDBuses.dequeue(temp);
        temp.PrintBusInfo();
        tempQueue.enqueue(temp);
    }
    while(!tempQueue.isEmpty())
    {
        WaitingBCKBuses.dequeue(temp);
    }
    while (!WaitingBCKBuses.isEmpty())
    {
        WaitingBCKBuses.dequeue(temp);
        temp.PrintBusInfo();
        tempQueue.enqueue(temp);
    }
    while(!tempQueue.isEmpty())
    {
        WaitingBCKBuses.dequeue(temp);
    }
cout<<"--------------------------------------------------------------------";

}

void Station::SetStaionNum(int num)
{
    StationNumber = num;
}

int Station::GetNumofStations()
{
    return NumofStations;
}

void Station::SetNumofStations(int num)
{
    NumofStations = num;
}

//Prioirity:
//SP: aged->1 POD->2 pregnant->3
//WP:4
//NP:5

void Station::PassAdd(Passenger* passenger)
{
    if (passenger->getType() == "WP") {
        if (passenger->getDirection() == "FWD")
            WPWaitingFWD.enqueue(*passenger);
        else
            WPWaitingBCK.enqueue(*passenger);
    }

    else if (passenger->getType() == "SP") {
        if (passenger->getDirection() == "FWD")
            SPWaitingFWD.enqueue(*passenger, passenger->getPriority());
        else
            SPWaitingBCK.enqueue(*passenger, passenger->getPriority());
    }

    else if (passenger->getType() == "NP") {

        if (passenger->getDirection() == "FWD")
            NPWaitingFWD.enqueue(*passenger);
        else
            NPWaitingBCK.enqueue(*passenger);
    }

}

void Station::PassPromote()
{
    Passenger passenger;
    if (NPWaitingFWD.peek(passenger)) {
        while (passenger.getWaitingTime() >= passenger.getMaxW()) {
            NPWaitingFWD.dequeue(passenger.getId());
            passenger.setType("SP");
            SPWaitingFWD.enqueue(passenger, 3);

            if (!NPWaitingFWD.peek(passenger)) {
                break;
            }
        }
    }
    Passenger passenger2;
    if (NPWaitingBCK.peek(passenger2)) {
        while (passenger2.getWaitingTime() >= passenger2.getMaxW()) {
            NPWaitingBCK.dequeue(passenger.getId());
            passenger.setType("SP");
            SPWaitingBCK.enqueue(passenger2, 3);

            if (!NPWaitingBCK.peek(passenger2)) {
                break;
            }
        }
    }
}

void Station::BusAdd(Bus* bus)
{
    if (bus->GetBusDirection() == "FWD")
        WaitingFWDBuses.enqueue(*bus);

    else
        WaitingBCKBuses.enqueue(*bus);

}



void Station::BusLeave(Company P)
{
    Bus bus;
    if (bus.GetBusDirection() == "FWD") {
        if (bus.BusIsFull() || (SPWaitingFWD.isEmpty() && NPWaitingFWD.isEmpty())) {
            WaitingFWDBuses.dequeue(bus);
        }

    }
    else {
        if (bus.BusIsFull() || (SPWaitingBCK.isEmpty() && NPWaitingBCK.isEmpty()))
            WaitingBCKBuses.dequeue(bus);
    }
    P.ToMoving(bus);
}
void Station::BusBoarding(Company* C, Time T)
{
     Bus* bus;
    while (!C->IsOff(T)) {
        if (bus->GetBusDirection() == "FWD") {
            if (bus->GetBusType() == "WBus") {
                while (!bus->BusIsFull() && !WPWaitingFWD.isEmpty()) {
                    Passenger P;
                    WPWaitingFWD.dequeue(P);
                    bus->GetPassOn(&P);
                }
            }
            else if (bus->GetBusType() == "MBus")
            {
                while (!bus->BusIsFull() && !SPWaitingFWD.isEmpty())
                {
                    Passenger P;
                    SPWaitingFWD.dequeue(P);
                    bus->GetPassOn(&P);
                }
                if (SPWaitingFWD.isEmpty())
                {
                    while (!bus->BusIsFull() && !NPWaitingFWD.isEmpty())
                    {
                        Passenger P;
                        NPWaitingFWD.dequeue(P.getId());
                        bus->GetPassOn(&P);
                    }
                }
            }
        }

        else if (bus->GetBusDirection() == "BCK") {
            if (bus->GetBusType() == "WBus") {
                while (!bus->BusIsFull() && !WPWaitingBCK.isEmpty()) {
                    Passenger P;
                    WPWaitingBCK.dequeue(P);
                    bus->GetPassOn(&P);
                }
            }
            else if (bus->GetBusType() == "MBus") {
                while (!bus->BusIsFull() && !SPWaitingBCK.isEmpty()) {
                    Passenger P;
                    SPWaitingBCK.dequeue(P);
                    bus->GetPassOn(&P);
                }
                if (SPWaitingBCK.isEmpty()) {
                    while (!bus->BusIsFull() && !NPWaitingBCK.isEmpty()) {
                        Passenger P;
                        NPWaitingBCK.dequeue(P.getId());
                        bus->GetPassOn(&P);
                    }
                }
            }
        }
    }
}
//rehab
void Station::RemovePassenger(int ID) {
    Node <Passenger> *LeftPass;
    LeftPass = NPWaitingBCK.SearchforPassenger(ID);
    delete LeftPass;
}
void Station::BusOffBoarding(Company* c )
{
    //Rehab Edited
    Passenger* passenger;
    Bus bus;
    LinkedQueue<Bus>temp;
    while(!WaitingBCKBuses.isEmpty())
    {
        WaitingBCKBuses.dequeue(bus);
        while(!bus.BusIsEmpty())
        {
            passenger=bus.GetPassOff(this->GetStaionNum());
            if(passenger->getEndStation()==StationNumber)
            {
                c->AddPassToFinishList(passenger);
            }
        }
        temp.enqueue(bus);
    }
    temp.dequeue(bus);
    WaitingFWDBuses.enqueue(bus);
    while(!WaitingFWDBuses.isEmpty())
    {
        WaitingFWDBuses.dequeue(bus);
        while(!bus.BusIsEmpty())
        {
            passenger=bus.GetPassOff(this->GetStaionNum());
            if(passenger->getEndStation()==StationNumber)
            {
                c->AddPassToFinishList(passenger);
            }
        }
        temp.enqueue(bus);
    }
    temp.dequeue(bus);
    WaitingFWDBuses.enqueue(bus);
}
//Rehab
void Station::ExecuteoneMinute(Company c,Time currentTime)
{
    BusOffBoarding(Company* c );
    PassPromote();
    BusBoarding(&c,currentTime);

}
//Rehab
bool Station::waitingPassengers()
{
    return SPWaitingFWD.isEmpty()&&SPWaitingBCK.isEmpty()&&WPWaitingFWD.isEmpty()&&WPWaitingBCK.isEmpty()&& NPWaitingBCK.isEmpty()&&NPWaitingFWD.isEmpty();
}

//Raneem Tamer
void Station::BoardingSPForOneMinute()
{
   /* // Board SP passengers for one minute
    cout << "Boarding SP for one minute:" << endl;

    // Boarding Forward direction SP passengers
    while (!SPWaitingFWD.isEmpty() && SPWaitingFWD.peekPriority() <= 3) {
        Passenger P;
        SPWaitingFWD.dequeue(P);

        // Check the priority and board accordingly
        if (P.getPriority() == 1) {
            cout << "Boarding Aged SP passenger " << P.getId() << " in Forward direction" << endl;
        }
        else if (P.getPriority() == 2) {
            cout << "Boarding POD SP passenger " << P.getId() << " in Forward direction" << endl;
        }
        else if (P.getPriority() == 3) {
            cout << "Boarding Pregnant SP passenger " << P.getId() << " in Forward direction" << endl;
        }
    }

    // Boarding Backward direction SP passengers
    while (!SPWaitingBCK.isEmpty() && SPWaitingBCK.peekPriority() <= 3) {
        Passenger P;
        SPWaitingBCK.dequeue(P);

        // Check the priority and board accordingly
        if (P.getPriority() == 1) {
            cout << "Boarding Aged SP passenger " << P.getId() << " in Backward direction" << endl;
        }
        else if (P.getPriority() == 2) {
            cout << "Boarding POD SP passenger " << P.getId() << " in Backward direction" << endl;
        }
        else if (P.getPriority() == 3) {
            cout << "Boarding Pregnant SP passenger " << P.getId() << " in Backward direction" << endl;
        }
    }*/
}


void Station::BoardingWPForOneMinute() {
    // Board WP passengers for one minute
    cout << "Boarding WP for one minute:" << endl;

    // Boarding Forward direction WP passengers
    while (!WPWaitingFWD.isEmpty()) {
        Passenger P;
        WPWaitingFWD.dequeue(P);
        cout << "Boarding WP passenger " << P.getId() << " in Forward direction" << endl;
    }

    // Boarding Backward direction WP passengers
    while (!WPWaitingBCK.isEmpty()) {
        Passenger P;
        WPWaitingBCK.dequeue(P);
        cout << "Boarding WP passenger " << P.getId() << " in Backward direction" << endl;
    }
}

void Station::BoardingNPForOneMinute() {
    // Board NP passengers for one minute
    cout << "Boarding NP for one minute:" << endl;

    // Boarding Forward direction NP passengers
    while (!NPWaitingFWD.isEmpty()) {
        Passenger P;
        NPWaitingFWD.dequeue(P.getId());
        cout << "Boarding NP passenger " << P.getId() << " in Forward direction" << endl;
    }

    // Boarding Backward direction NP passengers
    while (!NPWaitingBCK.isEmpty()) {
        Passenger P;
        NPWaitingBCK.dequeue(P.getId());
        cout << "Boarding NP passenger " << P.getId() << " in Backward direction" << endl;
    }
}

