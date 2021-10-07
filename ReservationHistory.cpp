#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

extern int inputAnInteger( int begin, int end );

// ReservationHistory default constructor
ReservationHistory::ReservationHistory( ReservationDatabase &theReservationDatabase,
                                        SouthboundTimetable &theSouthboundTimetable,
                                        NorthboundTimetable &theNorthboundTimetable )
   : idNumber(),
     reservationNumber(),
     reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
    cout << "\nEnter ID Number: ";
    cin >> idNumber;
    cout << "\nEnter Reservation Number: ";
    cin >> reservationNumber;
    cout << endl;

    if(!reservationDatabase.exist(idNumber, reservationNumber)) {
        cout << "\nReservation record not found." << endl;
        cin.ignore();
        return ;
    } 
    else {
        cout << "\nReservation Details \n\n";
        reservationDatabase.displayReservation(idNumber, reservationNumber);
    }
   
    int choice;
    while (true)
    {
        cout << "\nEnter Your Choice\n"
            << "1. Cancellation\n"
            << "2. Reduce\n"
            << "3. End";
        cin.ignore();

        do cout << "\n? ";
        while ((choice = inputAnInteger(1, 3)) == -1);
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            reservationDatabase.cancelReservation(idNumber, reservationNumber);
            return;
        }
        case 2:
            reservationDatabase.reduceSeats(idNumber, reservationNumber);
            return;
        case 3:
            return;
        default: // display error if user does not select valid choice
            cerr << "Incorrect Choice!\n";
            break;
        }
    }
}