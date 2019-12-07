#include "timetable.h"

TableElement::TableElement() {};

TableElement::TableElement(int s, int e, Time d) 
{
	start = s;
	end = e;
	departure = d;
}

void TableElement::showInfo()
{
	cout << "Source: " << start << "Destination: " << end << "Departure time: " << departure.hour << ":" << departure.minute << endl;
}

Time::Time() {};

Time::Time(int h, int m)
{
	hour = h;
	minute = m;
}

void Time::setTime(int h, int m)
{
	hour = h;
	minute = m;
}


TimeTable::TimeTable() {};

TimeTable::TimeTable(Map map)
{
	setTimeTable(map);
}

void TimeTable::setTimeTable(Map map)
{
	int count = 0;
	for (size_t i = 0; i < 26; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (map.getEdge(i, j))
			{
				table[0][count].start = i;
				table[0][count].end = j;
				table[0][count].departure.setTime(rand() % 24, rand() % 60);
				++count;
			}

		}
	}
	for (size_t i = 1; i < 31; i++)
	{
		memcpy(table[i], table[0], sizeof(table[0]));
		for (size_t j = 0; j < count; j++)
		{
			table[i][j].departure.setTime(rand() % 24, rand() % 60);
		}
	}
}

void TimeTable::showTimeTable(int day)
{
	for (int i = 0; i < 100; i++)
	{
		table[day][i].showInfo();
	}
}

TableElement TimeTable::getElement(int day, int index)
{
	return table[day][index];
}

TimeTable::~TimeTable() {};