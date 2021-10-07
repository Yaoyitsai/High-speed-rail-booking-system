// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"
extern int inputAnInteger(int begin, int end);

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
    fstream input;
    input.open("Reservation details.dat",ios::binary|ios::in);
    Reservation tmp;
    while (input.read(reinterpret_cast<char*>(&tmp), sizeof(tmp))) {
        reservations.push_back(tmp);
    }
    input.close();
}

void ReservationDatabase::storeReservations()
{
    fstream output;
    output.open("Reservation details.dat", ios::binary | ios::out);
    for (int i = 0; i < reservations.size(); i++) {
        output.write(reinterpret_cast<char*>(&reservations[i]), sizeof(reservations[i]));
    }
    output.close();
}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "Reservation Cancelled.\n\n";
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats( string idNumber, string reservationNumber )
{
    vector< Reservation >::iterator it = searchReservation(idNumber, reservationNumber);
    int choice;
    do cout << "\nHow many adult tickets to cancel ?";
    while ((choice = inputAnInteger(0, it->getAdultTickets())) == -1);
    it->setAdultTickets(it->getAdultTickets() - choice);

    do cout << "\nHow many concession tickets to cancel ?";
    while ((choice = inputAnInteger(0, it->getConcessionTickets())) == -1);
    it->setConcessionTickets(it->getConcessionTickets() - choice);
    cout << endl;
    
    this->displayReservation(idNumber, reservationNumber);
    this->storeReservations();
    cout << "\nYou have successfully reduced the number of tickets!\n\n";
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}