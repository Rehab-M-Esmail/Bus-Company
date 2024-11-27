//
// Created by Rehab Mahmoud on 29/12/2023.
//

#include "Time.h"
/*
void Time:: operator <<()
{
    cout<<Hour<<":"<<Minute;
}
*/

bool Time:: operator/(int counter)
{
    return (Minute/counter);
}

Time Time::operator+(const Time& other) const
{
    int h = Hour + other.Hour;
    int m = Minute + other.Minute;

    if (m >= 60)
    {
        h = h + m / 60;
        m = m % 60;
    }

    if (h >= 24)
    {
        h = h % 24;
    }

    return Time(h, m);
}
bool Time::operator==( Time& other)
{
    return (Hour==other.getHour() && Minute==other.getMinute());
}
bool Time::operator<(Time secondtime)
{
    if(Hour<secondtime.getHour() ||Minute<secondtime.getMinute())
        return true;
    else
        return false;
}
Time Time::operator-( Time& other) const
{
    int h = Hour - other.getHour();
    int m = Minute - other.getMinute();

    if (m < 0)
    {
        h = h - 1;
        m = m + 60; //4:10 - 5:50
    }

    if (h < 0)
    {
        h = h + 24;
        return Time(h,m);
    }

}
Time Time::operator--(int)
{
    Minute--;
    return (Minute>60)? Time(getHour()+1,Minute-60):Time(getHour(),Minute);

}
int Time::getMinute()
{
    return Minute;
}
int Time::getHour()
{
    return Hour;
}
void Time::setHour(int hour)
{
    Hour=hour;
}
void Time::setminute(int minute)
{
    while(minute>60)
    {
        minute-=60;
        Hour++;
    }
    Minute=minute;

}
Time::Time(string time)
{
    stringstream  ss(time);
    string word;
    for(int i=0;i<2;i++)
    {
        while (!ss.eof())
        {
            getline(ss, word, ':');
            i==0?setHour(stoi(word)):setminute(stoi(word));
        }
    }
}
Time Time::operator++(int)
{
    Minute++;
    if (Minute > 60)
    {
        Hour++;
       Minute-=60; //4:10 - 5:50
    }
}
bool Time::operator==(const Time& other) const
{
    return Hour == other.Hour && Minute == other.Minute;
}
bool Time::operator>=(const Time& other) const
{
    if (Hour > other.Hour)
        return true;
    else if (Hour == other.Hour && Minute > other.Minute)
        return true;
    else
        return false;
}
bool Time::operator<=(const Time& other) const
{
    if (Hour < other.Hour)
        return true;
    else if (Hour == other.Hour && Minute < other.Minute)
        return true;
    else
        return false;
}