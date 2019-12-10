#include "AirlineHandler.h"

int AirlineHandler::calculatePrice(TableElement* list, int num, seatlevel level, Time& time)
{
	int result = 0;
	for (int i = 0; i < num; i++)
		result += map.getEdge(list[i].start, list[i].end);
	time.hour = result / 500;
	time.minute = (int)(((double)result / 500 - time.hour) * 60);
	result *= 60;
	// economy: 60won per kilometer
	if (level == BUSINESS)
		result *= 3; // business: economy*3
	else if (level == FIRST)
		result *= 7; // first: economy*7

	return result;
}

void AirlineHandler::showTimeTable(void)
{
	int day;
	cout << "\n************* See Timetable **************" << endl;
	cout << "What day do you want? ";
	cin >> day;
	table.showTimeTable(day);
}

void AirlineHandler::makeReservation(bool random_flag)
{
	char* input_name;
	char input_name_buf[1000] = { 0 };
	char input_src;
	char input_dest;
	int input_date;
	int temp;
	seatlevel level;
	TableElement* transfer_list;
	int transfer_num;
	Time flight_time;
	int arrival_date;
	Time departure;
	Time arrival;
	int price = 0;
	TreeNode* target;

	if (random_flag) {
		for (int i = 0; i < 4; i++)
			input_name_buf[i] = (char)(rand() % 26 + 97);
		input_name_buf[4] = 0;
		input_src = (char)(rand() % 26 + 97);
		do {
			input_dest = (char)(rand() % 26 + 97);
		} while (input_src == input_dest);
		input_date = rand() % 31 + 1;
		temp = rand() % 3;
	}
	else {
		cout << "\n*********** Make Reservation ************" << endl;
		cout << "Name : ";
		cin >> input_name_buf;
		cout << "Source : ";
		cin >> input_src;
		cout << "Destination : ";
		cin >> input_dest;
		
		if (input_src == input_dest) {
			cout << "Source and destination is same" << endl;
			return;
		}

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

	transfer_list = table.getOptimalRoute(input_src, input_dest, input_date, map, transfer_num, arrival_date, departure, arrival);
	if (transfer_list[0].start == -1) {
		if (!random_flag) cout << "Route does not exist." << endl << endl;
		delete[] transfer_list;
		return;
	}
	price = calculatePrice(transfer_list, transfer_num, level, flight_time);
	input_name = strdup(input_name_buf);
	Data data(input_name, reserv_num, input_src, input_dest,
		      departure, input_date, arrival, arrival_date,
		      transfer_list, transfer_num, level, price, flight_time);
	
	if (!random_flag) {
		cout << "\nBefore inserting" << endl;
		res.tree_info();
	}

	target = res.reservation_insert(data);
	if (target != NULL) {
		if (!random_flag) {
			cout << "\nReservation info" << endl;
			target->data->showInfo();
		}
		reserv_num++;
	}
	if (!random_flag) {
		cout << "\nAfter inserting" << endl;
		res.tree_info();
	}
	delete[] input_name;
	delete[] transfer_list;
}

void AirlineHandler::cancelReservation(void)
{
	int input_num;
	cout << "\n*********** Cancel Reservation ************" << endl;
	cout << "Please write your reservation number : ";
	cin >> input_num;
	cout << "\nBefore deleting" << endl;
	res.tree_info();
	res.reservation_delete(input_num);
	cout << "\nAfter deleting" << endl;
	res.tree_info();
}

void AirlineHandler::checkReservation(void)
{
	int input_num;
	TreeNode* target;
	cout << "\n*********** Check Reservation ************" << endl;
	cout << "Please write your reservation number : ";
	cin >> input_num;
	target = res.reservation_search(input_num);

	if (target->data != NULL) {
		cout << "\nReservation Info" << endl;
		target->data->showInfo();
	}
	else {
		cout << "\nInvalid reservation numer : " << input_num << endl;
	}
}

AirlineHandler::AirlineHandler(void)
	: reserv_num(0), map()
{
	srand(time(NULL));
	table.setTimeTable(map);
	while (reserv_num < 500)
		makeReservation(true);
}

void AirlineHandler::mainUI(void)
{
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
