#pragma once

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
};

class TimeTable
{
public:
	TimeTable();
	TimeTable(Map map);
	~TimeTable();

	void setTimeTable(Map map);
	TableElement getElement(int day, int index);
private:
	TableElement table[31][100];
};
