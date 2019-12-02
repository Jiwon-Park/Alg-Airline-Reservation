#include "Reservation.h"
#include "Map.h"
#include "timetable.h"
#define MAX_INDEX 100

class AirlineHandler {
private:
	Map map;
	TimeTable table;
	Reservation res;
	int reserv_num;
private:
	int calculatePrice(int flight_time, seatlevel level) {
		int result;

		/************************************
		Will be implemented soon
		************************************/

		return result;
	}

	void showTimeTable(void) {
		/***************************************
		And please make TableElement.showInfo() function.
		table.showTimeTable();
		****************************************/
	}

	void makeReservation(void) {
		string input_name;
		char input_src;
		char input_dest;
		int input_date;
		int temp;
		seatlevel level;
		TableElement* transfer_list;
		int transfer_num;
		int flight_time;
		int arrival_date;
		Time departure;
		Time arrival;
		int price;

		cout << "*********** Make Reservation ************" << endl;
		cout << "Name : ";
		cin >> input_name;
		cout << "Source : ";
		cin >> input_src;
		cout << "Destination : ";
		cin >> input_dest;
		cout << "Date : ";
		cin >> input_date;
		cout << "Seat level(0: First, 1: Business, 2: Economy): ";
		cin >> temp;

		switch (temp) {
		case 0:
			level = FIRST;
			break;
		case 1:
			level = BUSINESS;
			break;
		case 2:
			level = ECONOMY;
			break;
		default:
			cout << "Invalid input" << endl;
			return;
		};

		/******************************************
		                                                                                                    departure_time arrival_time
		map.getOptimalRoute(input_src, input_dest, date, transfer_list, transfer_num, flight_time, arrival_date, departure, arrival);
		                     ___________________________   _________________________________________________________________________
		                           input arguments                                         output arguments
		                                                 TableElement*      int&         int&         int&        Time&     Time&
		*******************************************/
		price = calculatePrice(flight_time, level);
		Data data(input_name, reserv_num, input_src, input_dest,
			      departure, input_date, arrival, arrival_date,
			      transfer_list, transfer_num, level, price, flight_time);

		if (res.reservation_insert(data)) reserv_num++;
	}

	void cancelReservation(void) {
		int input_num;
		cout << "*********** Cancel Reservation ************" << endl;
		cout << "Please write your reservation number : ";
		cin >> input_num;
		res.reservation_delete(input_num);
	}

	void checkReservation(void) {
		int input_num;
		Node* target;
		cout << "*********** Check Reservation ************" << endl;
		cout << "Please write your reservation number : ";
		cin >> input_num;
		target = res.reservation_search(input_num);

		if (target->data != NULL) {
			cout << "Reservation Info" << endl;
			target->data->showInfo();
		}
		else {
			cout << "Invalid reservation numer : " << input_num << endl;
		}
	}

public:
	AirlineHandler()
		: reserv_num(0)
	{
		table.setTimeTable(map);
	}
	bool mainUI(void) {
		int op = 0;
		bool result = true;
		cout << "Airline Reservation System" << endl << endl;
		cout << "1. See a time table" << endl;
		cout << "2. Make a reservation" << endl;
		cout << "3. Cancel a reservation" << endl;
		cout << "4. Check a reservation info" << endl;
		cout << "5. exit" << endl << endl;
		cout << "Select : ";
		cin >> op;

		switch (op) {
		case 1:
			showTimeTable();
			break;
		case 2:
			makeReservation();
			break;
		case 3:
			cancelReservation();
			break;
		case 4:
			checkReservation();
			break;
		case 5:
			cout << "\nSee you next time" << endl;
			result = false;
			break;
		default:
			cout << "Invalid input" << endl << endl;
			break;
		}

		return result;
	}
};

int main(void)
{
	AirlineHandler handler;
	while (handler.mainUI()) continue;
	return 0;
}