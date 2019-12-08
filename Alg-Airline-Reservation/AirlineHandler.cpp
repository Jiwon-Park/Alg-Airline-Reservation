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
	int calculatePrice(TableElement* list, int num, seatlevel level) {
		int result = 0;

		//////////////////////////////////////////////////////////////
		cout << "calculatePrice" << endl;
		for (int i = 0; i < num; i++) {
			cout << list[i].start << " " << list[i].end << endl;
			result += map.getEdge(list[i].start, list[i].end);
		}
		result *= 60;
		// economy: 60won per kilometer
		if (level == BUSINESS)
			result *= 3; // business: economy*3
		else if (level == FIRST)
			result *= 7; // first: economy*7

		return result;
	}

	void showTimeTable(void) {
		int day;
		cout << "What day do you want? ";
		cin >> day;
		table.showTimeTable(day);
	}

	void makeReservation(bool random_flag=false) {
		///////////////////////////////////////////
		cout << "makeReservation" << endl;
		///////////////////////////////////////////
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
		int price = 0;

		if (random_flag) {
			char random_name[4];
			for (int i = 0; i < 4; i++)
				random_name[i] = (char)(rand() % 26 + 97);
			input_name = random_name;
			input_src = (char)(rand() % 26 + 97);
			do {
				input_dest = (char)(rand() % 26 + 97);
			} while (input_src == input_dest);
			input_date = rand() % 32;
			temp = rand() % 3;
		}
		else {
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
		}
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

		//////////////////////////////////////
		cout << "getOptimalRoute" << endl;
		//////////////////////////////////////
		transfer_list = table.getOptimalRoute(input_src, input_dest, input_date, map, transfer_num, arrival_date, departure, arrival);
		price = calculatePrice(transfer_list, transfer_num, level);
		
		///////////////////////////////////////////
		cout << "Data" << endl;
		///////////////////////////////////////////
		Data data(input_name, reserv_num, input_src, input_dest,
			      departure, input_date, arrival, arrival_date,
			      transfer_list, transfer_num, level, price, flight_time);

		////////////////////////////////
		cout << "reservation_insert"<<endl;
		////////////////////////////////
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
		TreeNode* target;
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
	AirlineHandler(void)
		: reserv_num(0), map()
	{
		srand(time(NULL));
		table.setTimeTable(map);
		for (int i = 0; i < 500; i++)
			makeReservation(true);
	}
	void mainUI(void) {
		int op = 0;
		bool flag = true;
		while (flag) {
			cout << "********** Airline Reservation System **********" << endl << endl;
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
				flag = false;
				break;
			default:
				cout << "Invalid input" << endl << endl;
				break;
			}
		}
	}
};

int main(void)
{
	AirlineHandler handler;
	handler.mainUI();
	return 0;
}