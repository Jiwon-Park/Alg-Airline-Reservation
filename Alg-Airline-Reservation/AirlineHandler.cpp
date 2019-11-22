#include <iostream>

using namespace std;

class AirlineHandler {
private:
	// Map map;				graph
	// TimeTable table;		¾ë ¹»·ÎÇÏÁö?
	// Reservation res;		rb-tree

private:
	void showTimeTable(void) {
		// time table func
	}

	void makeReservation(void) {
		// make reservation func
	}

	void cancelReservation(void) {
		// cancel reservation func
	}

	void checkReservation(void) {
		// reservation info func
	}

public:
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