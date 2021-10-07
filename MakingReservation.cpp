// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger( int begin, int end );

extern string departureTimes[ 37 ];

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
}

void MakingReservation::execute()
{
   if( chooseTrain() ) // displays timetables for 10 coming trains, then let user choose a train
   {
      inputReservationDetails();

      inputContactPersonInfo();

      reservationDatabase.addReservation( reservation );

      cout << "\nReservation Completed!\n\n";
   }
   else
      cout << "\nSorry! No train is available!\n\n";
}

bool MakingReservation::chooseTrain()
{
    int choice;
    int departureTime;
    do {
        cout << "\nOrigin Station" << endl;
        cout << "1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n6. Miaoli\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying\n?";
    } while ((choice = inputAnInteger(1, 12)) == -1);
    reservation.setOriginStation (choice);

    do {
        cout << "\n\nDestination Station" << endl;
        cout << "1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n6. Miaoli\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying\n?";
    } while ((choice = inputAnInteger(1, 12)) == -1 || choice == reservation.getOriginStation());
    reservation.setDestinationStation( choice);

    do {
        cout << "\n\nDeparture Time\n";
        for (int i = 1; i <= 36; i++) {
            cout << std::right << setw(2) << i << ". " << departureTimes[i] << endl;
        }cout << "?";
    } while ((choice = inputAnInteger(1, 36)) == -1);
    departureTime = choice;

    if (reservation.getOriginStation() < reservation.getDestinationStation()) {
        if (southboundTimetable.trainsAvailable(departureTime, reservation.getOriginStation(), reservation.getDestinationStation()))
            southboundTimetable.displayComingTrains(departureTime, reservation.getOriginStation(), reservation.getDestinationStation());
        else {
            return false;
        }
    }
    else {
        if(northboundTimetable.trainsAvailable(departureTime, reservation.getOriginStation(), reservation.getDestinationStation()))
           northboundTimetable.displayComingTrains(departureTime, reservation.getOriginStation(), reservation.getDestinationStation());
        else {
            return false;
        }
    }

    string theTrainNumber;
    cout << "\n\nEnter Train Number: ";
    cin >> theTrainNumber;

    reservation.setTrainNumber(theTrainNumber);

    return true;
}

void MakingReservation::inputReservationDetails()
{
   cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";
   cin.ignore();
   int carClass;
   do cout << "\n? ";
   while( ( carClass = inputAnInteger( 1, 2 ) ) == -1 );
   reservation.setCarClass( carClass );

	cout << "\nDeparture Date: ";

   char date[12];
   cin >> date;
   reservation.setDate( date );
   cin.ignore();

	cout << "\nHow many adult tickets? ";

   int adultTickets;
   cin >> adultTickets;
   reservation.setAdultTickets( adultTickets );

	cout << "\nHow many concession tickets? ";

   int concessionTickets;
   cin >> concessionTickets;
   reservation.setConcessionTickets( concessionTickets );

   cout << "\nTrip Details\n\n";
   reservation.displayReservationDetails();
}

void MakingReservation::inputContactPersonInfo()
{
   cout << "\nEnter Contact Person Information\n\n";

   cout << "ID Number: ";
   string idNumber;
   cin >> idNumber;
   reservation.setIdNumber( idNumber );

   cout << "\nPhone: ";
   string phone;
   cin >> phone;
   cin.ignore();
   reservation.setPhone( phone );

   srand( static_cast< unsigned int >( time( 0 ) ) );
   char reservationNumber[ 12 ];
   for( int i = 0; i < 8; i++ )
      reservationNumber[ i ] = rand() % 10 + '0';
   reservationNumber[ 8 ] = '\0';
   reservation.setReservationNumber( reservationNumber );
   
	cout << "\nReservation Number: " << reservationNumber << endl;
}