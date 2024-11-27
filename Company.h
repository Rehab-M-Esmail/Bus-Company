#pragma once
#include "Station.h"
#include <sstream>
#include "Event.h"
#include "LinkedList.h"
#include"Bus.h"
#include "Time.h"
#include <fstream>
#include <string.h>
#include"Queue"
class Company{
private:
    LinkedQueue<Event*> Events;
    Station* Stations; //dynamique?? Stations contains Values of Station
    LinkedQueue<Passenger*> FinishList;
    LinkedQueue<Bus>MBusCheckUp;//Check up queue for MBus
    LinkedQueue<Bus>WBusCheckUp;
    LinkedQueue<Bus>StationZero;
    LinkedQueue<Bus> FWDMovingBuses;
    LinkedQueue<Bus>BCKMovingBuses;
    int ComanyData[12];
    //Bus should have an atrribute stating the check in and out time,

public:

    //Insert a passenger to finish list
    void AddPassToFinishList(Passenger* Finishedpass)
    {
        FinishList.enqueue(Finishedpass);
    }
    bool IsOff(Time CurrentTime) {
        if (CurrentTime.getHour()>= 22 && CurrentTime.getHour() >= 4) {
            return true;
        }
        return false;

    }

    //release a bus
 /*   void Moving2Waiting(Time currentTime)
    {
//        released =StationZero.Dequeue();
        LinkedQueue<Bus>temp;
        Bus finished;
        while(!FWDMovingBuses.isEmpty())
        {

            FWDMovingBuses.peek(finished);
            if(finished.GeTArrialTime()==currentTime)
            {
                FWDMovingBuses.dequeue(finished);
                Stations[finished.GetNextStation()].BusAdd(&finished);
            }
            else
            {
                temp.enqueue(finished);
            }
        }
        while(!temp.isEmpty())
        {
            temp.dequeue(finished);
            FWDMovingBuses.enqueue(finished);
        }
        while(!BCKMovingBuses.isEmpty())
        {

            BCKMovingBuses.peek(finished);
            if(finished.GeTArrialTime()+ComanyData[1]==currentTime)
      //The time the bus should leave is the time when added to moving list+ the time between 2 stations
            {
                BCKMovingBuses.dequeue(finished);
                Stations[finished.GetNextStation()].BusAdd(&finished);
            }
            else
            {
                temp.enqueue(finished);
            }
        }
        while(!temp.isEmpty())
        {
            temp.dequeue(finished);
            BCKMovingBuses.enqueue(finished);
        }
    }*/
    void ToMoving(Bus& Moved)
    {
        if (Moved.GetBusDirection() == "FWD")
        {
            FWDMovingBuses.enqueue(Moved);
        }
        else
        {
            BCKMovingBuses.enqueue(Moved);
        }
    }
    void releaseFromCheckup(Time current)
    {
        LinkedQueue<Bus> TempQueue;
        Bus TempBus;
        while(!WBusCheckUp.isEmpty())
        {
           WBusCheckUp.peek(TempBus);
           if(TempBus.GeTArrialTime()+TempBus.GetMaintainDuration()==current)//Check if The buse Finish its checkup duration
           {
               WBusCheckUp.dequeue(TempBus);
               ToMoving(TempBus);
           }
           else
           {
               WBusCheckUp.dequeue(TempBus);
               TempQueue.enqueue(TempBus);
           }
        }
        while(!TempQueue.isEmpty())
        {
            TempQueue.dequeue(TempBus);
            WBusCheckUp.enqueue(TempBus);
        }
        while(!MBusCheckUp.isEmpty())
        {
            MBusCheckUp.peek(TempBus);
            if(TempBus.GeTArrialTime()+TempBus.GetMaintainDuration()==current)
            {
                MBusCheckUp.dequeue(TempBus);
                ToMoving(TempBus);
            }
            else
            {
                MBusCheckUp.dequeue(TempBus);
                TempQueue.enqueue(TempBus);
            }
        }
        while(!TempQueue.isEmpty())
        {
            TempQueue.dequeue(TempBus);
            MBusCheckUp.enqueue(TempBus);
        }

    }
    // Move a bus from Moving Buses List to Buses waiting at station
    // when the current time is time of bus arrival at its next station. (through station class)
    void moveToStation(Bus& ArrivedBus)
    {
        if(ArrivedBus.GetBusDirection() == "FWD")
        {
            Stations[ArrivedBus.GetNextStation()].BusAdd(&ArrivedBus);//Enqueue the bus to FWDList in the nextStation of the bus.
            ArrivedBus.SetNextStation(ArrivedBus.GetNextStation()+1);
        }
        // Ths Station will check the direction of the bus and add it to the appropriate list
        else
        {
             Stations[ArrivedBus.GetNextStation()].BusAdd(&ArrivedBus);
             ArrivedBus.SetNextStation(ArrivedBus.GetNextStation()+1);
        }
    }
    //Inserts a bus to checkup List
    void InsertToCheckup(Bus& TobeChecked)
    {
        if(TobeChecked.GetBusType()=="WBus")
        {
            WBusCheckUp.enqueue(TobeChecked);
        }
        else
        {
            MBusCheckUp.enqueue(TobeChecked);
        }
    }

    void CreateStations(int number){
       Stations= new Station[number];
    };
    //should be filled alternatively from each bus type
    //to be able to release one bus from each type every 15 minutes
    void CreateBuses(int Wnumber,int Wcapacity,int Mnumber,int Mcapacity,int wDuration,int mDuration,int bustrips)
    {
        LinkedQueue<Bus> WBuses;
        LinkedQueue<Bus> MBuses;

        for(int i=1;i<=Wnumber;i+=2)
        {
            Bus tempBus(i,"WBus",Wcapacity,wDuration,bustrips);
            WBuses.enqueue(tempBus);
        }
        for(int i=2;i<=Mnumber;i+=2)
        {
            Bus tempBus(i,"MBus",Mcapacity,mDuration,bustrips);
            MBuses.enqueue(tempBus);
        }
        //merging WBuses & MBuses
        for(int i=1;i<=Wnumber+Mnumber;i++)
        {
            //need to be tested to check the inequality bus numbers
            Bus dequeued;
            WBuses.dequeue(dequeued);
          //  Stations[0].BusAdd(dequeued);
            StationZero.enqueue(dequeued);
            MBuses.dequeue(dequeued);
            StationZero.enqueue(dequeued);
        }
    }
   void loadFile(ifstream& outfile)
   {
       int counter=0;
       while (outfile) {
           if(counter<11)
           {
               for (int i = 0; i < 11; i++)
               {
                   outfile >> ComanyData[i];
                   counter++;
               }
           }
           else
           {
               string Eventline;
               while (getline(outfile, Eventline))
               {
                  string EventData[6];
                   stringstream ss(Eventline);//This part will split the Event line string and store it in  word
                   string word;
                   while (!ss.eof())
                   {
                       getline(ss, word,' ');
                       //Store the Data of Each event in an array
                       for(int i=0;i<6;i++)
                       {
                           EventData[i];
                       }
                   }
                   for(int i=1;i<ComanyData[11];i++)
                   {
                   if(EventData[0]=="A")
                   {

                       Time t(EventData[2]);
                       if(EventData[3]<EventData[4])
                       {
                           //Passenger tempPass("FWD",EventData[1],t,stoi(EventData[3]),stoi(EventData[4]),stoi(EventData[5]));
                           //Arrival* A = new Arrival(tempPass);
                           Arrival* A = new Arrival("FWD",EventData[1],t,stoi(EventData[3]),stoi(EventData[4]),stoi(EventData[5]),this);
                           Events.enqueue(A);
                       }
                       else
                       {
                           //Passenger tempPass("BCK",EventData[1],t,stoi(EventData[3]),stoi(EventData[4]),stoi(EventData[5]));
                           Arrival* A = new Arrival("BCK",EventData[1],t,stoi(EventData[3]),stoi(EventData[4]),stoi(EventData[5]),this);
                           Events.enqueue(A);
                       }

                   }
                   else
                   {
                       Time t(EventData[1]);
                       Leave* LEAVE =new Leave(stoi(EventData[2]),stoi(EventData[3]),this);
                       Events.enqueue(LEAVE);
                   }
                   }
               }
               outfile.close(); // Close the file when done
           }
           CreateStations(ComanyData[0]);
           CreateBuses(ComanyData[2],ComanyData[4],ComanyData[3],ComanyData[4],ComanyData[7],ComanyData[8],ComanyData[6]);//
           Events.SetCount(ComanyData[11]);
       }
   }
   //Rehab
   void printOutput(Time current)
   {
        char n='T';

            for (int i = 1; i < ComanyData[0]; i++)
            {
                while(n)
                {
                cout << "================================= STATION #" << i << "==============================";
                Stations[i].printStatus();
                cout << MBusCheckUp.GetCount() + WBusCheckUp.GetCount() << "In-checkup Buses : ";
                // print Check up buses IDs
                LinkedQueue<Bus> tempQueue;
                Bus temp;
                while (!MBusCheckUp.isEmpty()) {
                    MBusCheckUp.dequeue(temp);
                    cout << temp.GetBusID();
                    tempQueue.enqueue(temp);
                }
                while (!tempQueue.isEmpty()) {
                    tempQueue.dequeue(temp);
                    MBusCheckUp.dequeue(temp);
                }
                while (!WBusCheckUp.isEmpty()) {
                    WBusCheckUp.dequeue(temp);
                    cout << temp.GetBusID();
                    tempQueue.enqueue(temp);
                }
                while (!tempQueue.isEmpty()) {
                    tempQueue.dequeue(temp);
                    WBusCheckUp.dequeue(temp);
                }
                Passenger *tempPassenger;
                LinkedQueue<Passenger> tempPassengersQueue;
                while (!FinishList.isEmpty()) {
                    FinishList.dequeue(tempPassenger);
                    if (tempPassenger->GetFinishTime() == current) {
                        cout << tempPassenger->getId();
                        tempPassengersQueue.enqueue(*tempPassenger);
                    }
                    //Return the finish list as it's
                    while (!tempPassengersQueue.isEmpty()) {
                        tempPassengersQueue.dequeue(*tempPassenger);
                        FinishList.enqueue(tempPassenger);
                    }
                }

            }
            cout << "Print any key to display next Station";
            cin >> n;
        }
   }
   void ExecutecurrentEvents(Time currentTime)
   {
        //--edit
       releaseFromCheckup(currentTime);
       //fromCheck2Moving(currentTime);
       releaseFromCheckup(currentTime);
       for (int i=1;i<=ComanyData[0];i++)
       {
           Stations[i].ExecuteoneMinute(this,currentTime);
           cout<<"Current Time(Hour: Min)==> "<<currentTime.getHour()<<":"<<currentTime.getMinute();
           printOutput(currentTime);
       }
        while(! Events.isEmpty())
        {
            Event* temp;
            Events.peek(temp);
            if(temp->GetEventTime()==currentTime)
            {
                Events.dequeue(temp);
                temp->Execute();
            }
        }
   }
   Station returnStationPTR(int Stationnum)
   {
       return Stations[Stationnum];
   }
   int GetFinishCounter()
   {
       return FinishList.GetCount();
   }
    int getNPcounter()
    {
        int NPcount=0,WPcount=0;
        while (!FinishList.isEmpty())
        {
            Passenger* temp;
            FinishList.dequeue(temp);
            if(temp->getType()=="NP")
                NPcount++;
        }
    }
    int GetSPcounter()
    {
        int SPcount=0;
        while (!FinishList.isEmpty())
        {
            Passenger* temp;
            FinishList.dequeue(temp);
            if(temp->getType()=="SP")
                SPcount++;
        }
        return SPcount;
    }
    int GetWPcounter()
    {
        int WPcount=0;
        while (!FinishList.isEmpty())
        {
            Passenger* temp;
            FinishList.dequeue(temp);
            if(temp->getType()=="SP")
                WPcount++;
        }
        return WPcount;
    }
    void GetBusesData()
    {
       cout<<"Buses: "<<ComanyData[2]+ComanyData[3]<<" WBus:"<<ComanyData[2]<<",MBus: "<<ComanyData[3];
    }
    void GetAVGwaitTime()
    {
        Passenger* temp;
        int AVGtime;
        while (!FinishList.isEmpty())
        {
            FinishList.dequeue(temp);
            AVGtime+(temp->getWaitingTime());
        }
      AVGtime=AVGtime/(GetFinishCounter());
        cout<<"Passenger AVG Wait Time="<<AVGtime;//              needs improvement
    }
    void printFinishList()
    {
        Passenger* temp;

        while (!FinishList.isEmpty())
        {
            FinishList.dequeue(temp);
            temp->GetFinishTime();
            cout <<"  "<<temp->getId()<<"  ";
            temp->ptintArrivalTime();
            cout<<"  "<<temp->getWaitingTime()<<"  ";
            temp->GetTotalTime();
        }
    }/*
    void realseBus()
    {
        Bus released;
        StationZero.dequeue(released);
        ToMoving(released);
    }*/
    bool Passengersreached()
    //The function checks if all passengers in the whole simulation reaches their destination
    {
        int counter=0;
        for(int i=0;i<ComanyData[0];i++)
        {
            if(Stations[i].waitingPassengers())
                counter++;
        }
        if(counter==ComanyData[0])
            return true;
        else
            return false;
    }
    void PassAddToStation(Passenger& added)
    {
        Stations[added.getStartStation()].PassAdd(&added);
    }
    void Back2station(Bus& Backed)
    {
        StationZero.enqueue(Backed);
    }
    bool EventsIsempty()
    {
        return Events.isEmpty();
    }
   // Raneem Tamer output file
    void generateOutputFile(const string& outputFileName) ;
    /*{
        ofstream outputFile(outputFileName);

        if (!outputFile.is_open()) {
            cerr << "Error opening the output file.\n";
            return;
        }

        // header
        outputFile << "FT ID AT WT TT\n";

        // Loop through FinishList to generate output for each passenger
        while (!FinishList.isEmpty()) {
            Passenger* passenger;
            FinishList.dequeue(passenger);

            Time FT = passenger->GetFinishTime();
            int ID = passenger->getId();
            Time AT = passenger->getArrivalTime();
            int WT = passenger->getMoveTime() - AT;
            Time TT = passenger->GetFinishTime() - passenger->getMoveTime();
            outputFile << FT << " " << ID << " " << AT << " " << WT << " " << TT << "\n";

            delete passenger;
        }

        // Close the output file
        outputFile.close();
        cout << "Output file  generated successfully.\n";
    }*/
};

/*
 * ComanyData[0]=> #of stations
 * ComanyData[1]=>time between two stations;
 * ComanyData[2]=>W_Bus count
 * ComanyData[3]=>MBus_count
 * ComanyData[4]=>W_Bus capacity
 * ComanyData[5]=>M_Bus capacity
 * ComanyData[6]=> no of trips
 * ComanyData[7]=>C-WBus
 * ComanyData[8]=>C-MBus
 * ComanyData[9]=> WMax
 * ComanyData[10]=>get on/off time
 * ComanyData[11]=>EventsLines
 list ot pointers excute()
event pointer => peek to know if the time=time event then dequeue event list of pointers
 time class hh: mm
u need to check every array/queue in the list by printing its data EX queue of buses >> print the queue of buses
 */
