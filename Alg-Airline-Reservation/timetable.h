#ifndef __TIMETABLE_H__
#define __TIMETABLE_H__

#include "Map.h"

class Time
{
public:
	int hour, minute;
	Time();
	Time(const Time& ref);
	Time(int h, int m);
	void setTime(int h, int m);
	bool operator<(const Time right) const;
	bool operator>(const Time right) const;
	Time operator+(const Time right) const;
	Time operator+=(const Time right);
};

class TableElement
{
public:
	int start = -1;
	int end;
	Time departure;
	TableElement();
	TableElement(int s, int e, const Time d);
	TableElement& operator=(const TableElement& ref);
	void showInfo() const;
};

class TimeTable
{
public:
	TimeTable();
	TimeTable(Map map);
	~TimeTable();

	void setTimeTable(const Map map);
	void showTimeTable(int day) const;
	TableElement getElement(int day, int index) const;
	TableElement* getOptimalRoute(int start, int end, int day, const Map map, int& transfer_times, int& arrival_date, Time& departure_time, Time& arrival_time) const;
private:
	TableElement table[31][1000];
};

class queueelem
{
public:
	queueelem() {};
	queueelem(int i, int d) :index(i), day(d) { initialized = true; };
	~queueelem() {};
	void setelem(int index, int day, const Time time);
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
	void push(int index, int day, const Time time);
	void pop();
	queueelem front() const;
	bool empty() const;
};

#endif
