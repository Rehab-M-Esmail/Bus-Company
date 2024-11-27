
#include <iostream>
#include "Company.h"
#include "Event.h"
#include "Passenger.h"
#include<fstream>

int main() {
    //Testing spliting The string
    /*stringstream ss("Rehab Mahmoud Esmail");
    string word;
    while (!ss.eof()) {
        getline(ss, word,' ');
        cout << word << endl;
    }*/
    //to split the time
    /*stringstream  ss("4:10");
    string word;
    while (!ss.eof()) {
        getline(ss, word, ':');
        cout << word << endl;
    }*/

 Company c;
 //Simulation Function by Rehab
 ifstream outputfile;
 //outputfile.open("Input.txt");
 c.loadFile(outputfile);
 Time CompanyTime(4,00);
    //while loop that keeps looping till the events are Finished and the passengers reached their destination
    while (!c.EventsIsempty()&& c.Passengersreached())
    {
        c.ExecutecurrentEvents(CompanyTime);
        c.printOutput(CompanyTime);
        CompanyTime++;
    }
   // c.generateOutputFile()

//check the checkup,moving list;
    //Check if any buses should be realesed either from the station zero or the checkup list and so on
//generate the outputfile by rehab   sketching
/*for(int i=0;i<c.GetFinishCounter();i++)
{
    c.printFinishList();
}
cout<<"Passengers: "<<c.GetFinishCounter()<<"[ "<<"NP: "<<c.getNPcounter()<<", SP: "<<c.GetSPcounter()<<", WP: "<<c.GetWPcounter();
cout<<"Passengers Avg Wait time= ";
cout<<"Passengers Avg Wait time= ";
cout<<"Auto Promoted passengers: ";
c.GetBusesData();*/

//


    return 0;
   }
