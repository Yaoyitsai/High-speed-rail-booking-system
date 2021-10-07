// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
    fstream inFile("Southbound timetable.dat", ios::in | ios::binary);
    if (!inFile) {
        cout << "File could not be opened." << endl;
        exit(1);
    }

    Train unit, tmp;
    for (int i = 1; !inFile.eof(); i++) {
        if (inFile.eof() == 1)break;
        inFile.read(reinterpret_cast<char*>(&tmp), sizeof(Train));
        southboundTimetable.push_back(tmp);
    }
    inFile.close();
}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool SouthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    vector< Train >::iterator it = southboundTimetable.begin();
    for (; it != southboundTimetable.end(); ++it) {
        while (it->getDepartureTimes( originStation)[0] == '-') it++;
        if ((departureTimes[departureTime][0] - '0') * 1000 + (departureTimes[departureTime][1] - '0') * 100 +
            (departureTimes[departureTime][3] - '0') * 10 + (departureTimes[departureTime][4] - '0') <=
            ((it->getDepartureTimes(originStation)[0] - '0') * 1000 +
            (it->getDepartureTimes( originStation)[1] - '0') * 100 +
                (it->getDepartureTimes(originStation)[3] - '0') * 10 +
                (it->getDepartureTimes(originStation)[4] - '0'))) {
            if (it->getDepartureTimes(originStation)[0] != '-' && (it->getDepartureTimes(destinationStation)[0] != '-'))
                return true;
        }
    }
    return false;
}

void SouthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    vector< Train >::iterator tmp;
    cout << endl << std::right << setw(9) << "Train No." << std::right << setw(11) << "Departure" << std::right << setw(9) << "Arrival" << endl;
    vector< Train >::iterator it = southboundTimetable.begin();
    for (; it != southboundTimetable.end(); ++it) {
        while (it->getDepartureTimes(originStation)[0] == '-') it++;
        if ((departureTimes[departureTime][0] - '0') * 1000 + (departureTimes[departureTime][1] - '0') * 100 +
            (departureTimes[departureTime][3] - '0') * 10 + (departureTimes[departureTime][4] - '0') <=
            ((it->getDepartureTimes(originStation)[0] - '0') * 1000 +
            (it->getDepartureTimes(originStation)[1] - '0') * 100 +
                (it->getDepartureTimes(originStation)[3] - '0') * 10 +
                (it->getDepartureTimes(originStation)[4] - '0'))) {
            for (vector< Train >::iterator it2 = it; it2 < it + 10; it2++) {
                while (it2->getDepartureTimes(originStation)[0] == '-' ||
                    it2->getDepartureTimes(destinationStation)[0] == '-')
                {
                    it++, it2++;
                    if (it2 == southboundTimetable.end())break;
                }
                if (it2 == southboundTimetable.end()) break;
                cout << std::right << setw(9) << it2->getTrainNumber()
                    << std::right << setw(11) << it2->getDepartureTimes(originStation)
                    << std::right << setw(9) << it2->getDepartureTimes(destinationStation) << endl;
            }
            break;
        }
        if (strcmp((char*)&it->getTrainNumber(), "567") == 0)break; //add
    }

}

vector< Train >::iterator SouthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = southboundTimetable.begin();
   for( ; it != southboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return southboundTimetable.end();
}