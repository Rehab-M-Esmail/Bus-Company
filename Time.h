#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class Time {
private:
    int Hour;
    int Minute;
public:
    Time(string time);
    Time();
    Time(int hour,int min):Hour(hour),Minute(min){};
    Time(int min):Minute(min){};
    void setminute(int minute);
    void setHour(int hour);
    int getHour();
    int getMinute();
    Time operator--(int);
    Time operator-( Time& other) const;
    bool operator<(Time secondtime);
    bool operator==( Time& other);
    Time operator+(const Time& other) const;
    bool operator/(int counter);
    Time operator++(int);
    bool operator==(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator<=(const Time& other) const;

    //void operator <<();
    };
/*
#pragma once

#include <iostream>
#include <sstream>
using namespace std;

class Time {
private:
    int hour;
    int minute;
    int second;

public:
    Time(int h, int m, int s);
    Time();
    Time(int sec);

    int GetHour() const;
    void SetHour(int h);

    int GetMinute() const;
    void SetMinute(int m);

    int GetSecond() const;
    void SetSecond(int s);

    Time operator+(const Time& other) const;
    Time operator-(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator>=(const Time& other) const;
    Time operator--(int);
    bool operator<(Time secondtime);
    bool operator/(int countr);
    Time(string time);
};

Time::Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

Time::Time() : hour(0), minute(0), second(0) {}

Time::Time(int sec) : hour(0), minute(0), second(sec) {}

int Time::GetHour() const {
    return hour;
}

void Time::SetHour(int h) {
    if (h >= 0 && h < 24) {
        hour = h;
    }
    else {
        std::cout << "Invalid hour";
    }
}

int Time::GetMinute() const {
    return minute;
}

void Time::SetMinute(int m) {
    if (m >= 0 && m < 60) {
        minute = m;
    }
    else {
        std::cout << "Invalid minute";
    }
}

int Time::GetSecond() const {
    return second;
}

void Time::SetSecond(int s) {
    if (s >= 0 && s < 60) {
        second = s;
    }
    else {
        std::cout << "Invalid second";
    }

}

Time Time::operator+(const Time& other) const {
    int h = hour + other.hour;
    int m = minute + other.minute;
    int s = second + other.second;

    if (s >= 60) {
        m = m + s / 60;
        s = s % 60;
    }

    if (m >= 60) {
        h = h + m / 60;
        m = m % 60;
    }

    if (h >= 24) {
        h = h % 24;
    }

    return Time(h, m, s);
}

Time Time::operator-(const Time& other) const {
    int h = hour - other.hour;
    int m = minute - other.minute;
    int s = second - other.second;

    if (s < 0) {
        m = m - 1;
        s = s + 60;
    }

    if (m < 0) {
        h = h - 1;
        m = m + 60;
    }

    if (h < 0) {
        h = h + 24;
    }

    return Time(h, m, s);
}

bool Time::operator==(const Time& other) const {
    return hour == other.hour && minute == other.minute && second == other.second;
}

bool Time::operator>=(const Time& other) const {
    if (hour > other.hour) {
        return true;
    }
    else if (hour == other.hour && minute > other.minute) {
        return true;
    }
    else if (hour == other.hour && minute == other.minute && second >= other.second) {
        return true;
    }
    else {
        return false;
    }
}

bool Time:: operator/(int counter)
{
    return (minute / counter);
}


bool Time::operator<(Time secondtime)
{
    if (hour < secondtime.GetHour() || minute < secondtime.GetMinute())
        return true;
    else
        return false;
}

Time Time::operator--(int)
{
    second--;
    if (second < 0) {
        minute--;
        second += 60;
    }
    if (minute < 0) {
        hour--;
        minute += 60;
    }
    if (hour < 0) {
        hour += 24;
    }
    return *this;
}


Time::Time(string time)
{
    stringstream ss(time);
    string word;

    for (int i = 0; i < 3; i++)
    {
        getline(ss, word, ':');

        if (i == 0) {
            SetHour(stoi(word));
        }
        else if (i == 1) {
            SetMinute(stoi(word));
        }
        else if (i == 2) {
            SetSecond(stoi(word));
        }
    }
}*/
