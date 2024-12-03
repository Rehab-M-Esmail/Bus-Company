#pragma once
#include <iostream>
#include <string.h>
#include "Time.h"
#include "Bus.h"
using namespace std;


class Passenger {
private:
    int id;
    Time arrivalTime;
    int startStation;
    int endStation;
    int timeToGetOn;
    int timeToGetOff;
    int MaxW;
    int WaitingTime;
    string type;
    string subtype;
    string Direction;
    Time FinishTime;
    Time TotalTime;

public:
    Passenger(string direction,string type,Time t,int ID,int start,int End):Direction(direction),type(type),
                                                                            arrivalTime(t),id(ID),startStation(start),endStation(End){}
     Passenger();
    int getMaxW()
    {
        return MaxW;
    }

    void CalculateFT(Time PassengersGfT,Time BusReachedTime)
    {
        FinishTime=PassengersGfT+BusReachedTime+timeToGetOff;
    }
    void printFinishTime()
    {
        cout<< FinishTime.getHour() <<":"<<FinishTime.getMinute();
    }
    Time GetFinishTime()
    {
        return Time(FinishTime);
    }
    Time GetTotalTime()
    {
        return TotalTime;
    }
    void SetTripTime(Time MovedBusT)
    {
        TotalTime=FinishTime.operator-(MovedBusT);
    }


    int getWaitingTime()
    {
        return WaitingTime;
    }

    int getId() const {
        return id;
    }

    Time getArrivalTime() const {
        return arrivalTime;
    }
    void ptintArrivalTime()
    {
        cout<<arrivalTime.getHour();
        cout<<":";
        cout<<arrivalTime.getMinute();
    }


    int getStartStation() const {
        return startStation;
    }

    int getEndStation() const {
        return endStation;
    }

    int getPriority() const
    {
        if (type == "NP")
            return 1;
        else if(type == "WP")
            return 2;
        else if (type == "SP")
            if(subtype=="pregnant")
                return 3;
            else if(subtype=="POD")
                return 4;
            else if(subtype=="aged")
                return 5;
    }

    int getTimeToGetOn() const {
        return timeToGetOn;
    }

    int getTimeToGetOff() const {
        return timeToGetOff;
    }

    string getType() const {
        return type;
    }

    void setMaxW(int s)
    {
        MaxW = s;
    }

    void setWaitingTime(int t)
    {
        WaitingTime = t;
    }

    void setId(int newId) {
        id = newId;
    }

    void setArrivalTime(int newArrivalTime) {
        arrivalTime = newArrivalTime;
    }

    void setStartStation(int newStartStation) {
        startStation = newStartStation;
    }

    void setEndStation(int newEndStation) {
        endStation = newEndStation;
    }

    void setTimeToGetOn(int newTimeToGetOn) {
        timeToGetOn = newTimeToGetOn;
    }

    void setTimeToGetOff(int newTimeToGetOff) {
        timeToGetOff = newTimeToGetOff;
    }

    void setType(string newType) {
        type = newType;
    }

    void SetSubType(string s)
    {
        subtype = s;
    }

   /* int getWaitingTime(Time currentTime) const {
        return currentTime - arrivalTime;
    }
*/
    /*void displayInfo() const {
        cout << "ID: " << id << "\nArrival Time: " << arrivalTime
             << "\nStart Station: " << startStation << "\nEnd Station: " << endStation
             << "\nTime to Get On: " << timeToGetOn << "\nTime to Get Off: " << timeToGetOff
             << "\nPassenger Type: " << type << "\n\n";
    }*/


    /*bool operator<(const Passenger& other) const {
        return arrivalTime < other.getArrivalTime();

    }
*/
    //Rehab
    void printInfo()
    {
        cout<<Direction<<"["<<id<<"("<<subtype<<")] ";
    }
    string getDirection() const
    {
        return Direction;
    }

    string getSubType() const
    {
        return subtype;
    }
};

