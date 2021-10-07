// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"
using namespace std;
extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
    ifstream inFile("Northbound timetable.dat", ios::in | ios::binary);
    if (!inFile) {
        cout << "File could not be opened." << endl;
        exit(1);
    }

    Train unit, tmp;
    for (int i = 1; !inFile.eof(); i++) {
        //inFile >> northboundTimetable[i].trainNumber;
        if (inFile.eof() == 1)break;
        inFile.read(reinterpret_cast<char*>(&tmp), sizeof(Train));
        northboundTimetable.push_back(tmp);
    }
    inFile.close();
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    vector< Train >::iterator it = northboundTimetable.begin();
    for (; it != northboundTimetable.end(); ++it) {
        while (it->getDepartureTimes(13 - originStation)[0] == '-') it++;
        if ((departureTimes[departureTime][0] - '0') * 1000 + (departureTimes[departureTime][1] - '0') * 100 +
            (departureTimes[departureTime][3] - '0') * 10 + (departureTimes[departureTime][4] - '0') <=
            ((it->getDepartureTimes(13 - originStation)[0] - '0') * 1000 +
            (it->getDepartureTimes(13 - originStation)[1] - '0') * 100 +
                (it->getDepartureTimes(13 - originStation)[3] - '0') * 10 +
                (it->getDepartureTimes(13 - originStation)[4] - '0'))) {
            if (it->getDepartureTimes(originStation)[0] != '-' && (it->getDepartureTimes(destinationStation)[0] != '-'))
                return true;
        }
    }
    return false;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    vector<string> yes;
    vector< Train >::iterator tmp,it2;
    cout << endl << std::right << setw(9) << "Train No." << std::right << setw(11) << "Departure" << std::right << setw(9) << "Arrival" << endl;
    vector< Train >::iterator it = northboundTimetable.begin();
    for (; it != northboundTimetable.end(); ++it) {
        while (it->getDepartureTimes(13-originStation)[0] == '-') it++;
        if ((departureTimes[departureTime][0] - '0') * 1000 + (departureTimes[departureTime][1] - '0') * 100 +
            (departureTimes[departureTime][3] - '0') * 10 + (departureTimes[departureTime][4] - '0') <=
            ((it->getDepartureTimes(13 - originStation)[0] - '0') * 1000 +
            (it->getDepartureTimes(13 - originStation)[1] - '0') * 100 +
                (it->getDepartureTimes(13 - originStation)[3] - '0') * 10 +
                (it->getDepartureTimes(13 - originStation)[4] - '0'))) {
            for (vector< Train >::iterator it2 = it; it2 < it +10; it2++) {
                while (it2->getDepartureTimes(13 - originStation)[0] == '-' ||
                    it2->getDepartureTimes(13 - destinationStation)[0] == '-')
                {
                    it++, it2++;
                    if (it2 == northboundTimetable.end())break;
                }
                if (it2 == northboundTimetable.end()) break;
                yes.push_back(it2->getTrainNumber());
                cout << std::right << setw(9) << it2->getTrainNumber()
                    << std::right << setw(11) << it2->getDepartureTimes(13 - originStation)
                    << std::right << setw(9) << it2->getDepartureTimes(13 - destinationStation) << endl;
            }
            break;
        }
        if (strcmp((char*)&it->getTrainNumber(), "598") == 0)break; //add
    }
}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}