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
	bool operator<(const Time right);
	bool operator>(const Time right);
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
	TableElement* shortestPath(int start, int end, int day, int &transfer_times);
private:
	TableElement table[31][100];
};

class queueelem
{
public:
	queueelem() {};
	queueelem(int i, int d) :index(i), day(d) { initialized = true; };
	~queueelem() {};
	void setelem(int index, int day, Time time);
	int index, day;
	Time time;
	bool initialized = false;
	bool operator<(const queueelem right);
	bool operator>(const queueelem right);
};


class priority_queue
{
	queueelem e[1026];
	int count = 0;
	void swap(int idx1, int idx2);
public:
	priority_queue() {};
	~priority_queue() {};
	void push(int index, int day, Time time);
	void pop();
	queueelem top();
};

#endif
