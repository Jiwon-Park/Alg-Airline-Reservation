#ifndef __TIMETABLE_H__
#define __TIMETABLE_H__

#include "Map.h"

class Time
{
public:
	int hour, minute;
	Time();
	Time(int h, int m);
	void setTime(int h, int m);
};

class TableElement
{
public:
	int start;
	int end;
	Time departure;
	TableElement();
	TableElement(int s, int e, Time d);
	void showInfo();
};

class TimeTable
{
public:
	TimeTable();
	TimeTable(Map map);
	~TimeTable();

	void setTimeTable(Map map);
	void showTimeTable(int day);
	TableElement getElement(int day, int index);
private:
	TableElement table[31][100];
};
#endif
