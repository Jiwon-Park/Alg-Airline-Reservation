#ifndef __AIRLINEHANDLER_H__
#define __AIRLINEHANDLER_H__

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
	int calculatePrice(TableElement* list, int num, seatlevel level, Time& time);
	void showTimeTable(void);
	void makeReservation(bool random_flag=false);
	void cancelReservation(void);
	void checkReservation(void);
public:
	AirlineHandler(void);
	void mainUI(void);
};
#endif
