#include <iostream>
#include <vector>
using namespace std;

class Time {
public:
    int hour;
    int minute;

    // Constructor with default values (0 hours and 0 minutes)
    Time(int h = 0, int m = 0) : hour(h), minute(m) {}

    // Add a specified number of minutes to the time
    void addMinutes(int minutes) {
        int totalMinutes = hour * 60 + minute + minutes;
        hour = totalMinutes / 60;
        minute = totalMinutes % 60;
    }

    // Convert the time to total minutes
    int toMinutes() const {
        return hour * 60 + minute;
    }
};


class Bus {
public:
    string busType;

   
    Bus(const string& type) : busType(type) {}
};


class Station0 {
public:
    vector<Bus> buses[2];  // 0: MBus, 1: WBus
    int releaseInterval;        // Interval for releasing buses
    Time currentTime;           // Current time at the station


    Station0(int interval = 15) : releaseInterval(interval), currentTime() {}

   
    void addBuses(const string& busType, int count) {
        for (int i = 0; i < count; ++i) {
            buses[busTypeToIndex(busType)].emplace_back(busType);
        }
    }

    // Release a bus of the specified type from the station
    void releaseBuses(const string& busType) {
        // Get the index of the bus type (0 for MBus, 1 for WBus)
        int index = busTypeToIndex(busType);

        // Check if the index is valid and there are buses of that type
        if (index != -1 && !buses[index].empty()) {
            // Take the first bus of the specified type
            Bus releasedBus = buses[index].front();

            // Remove the released bus from the station
            buses[index].erase(buses[index].begin());

            // Print a message indicating the released bus
            cout << "Released " << releasedBus.busType << " bus from Station#0\n";


        }
    }
    // Simulate the passage of time by adding a specified number of minutes
    void simulateTimePassage(int minutes) {
        currentTime.addMinutes(minutes);

        // Check if the specified release interval has passed
        if ((currentTime.hour * 60 + currentTime.minute) % releaseInterval == 0) {
            cout << releaseInterval << " minutes have passed.\n";
        }
    }

private:
    // Convert a bus type string to an index (0 for MBus, 1 for WBus)
    int busTypeToIndex(const string& busType) {
        if (busType == "MBus") {
            return 0;
        }
        else if (busType == "WBus") {
            return 1;
        }
        else {
            // Handle unknown bus types
            return -1;
        }
    }
};
