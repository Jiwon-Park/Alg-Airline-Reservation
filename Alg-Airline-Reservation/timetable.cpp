#include "timetable.h"
#define min(a,b) a<b?b:a
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

bool Time::operator<(const Time right)
{
	if (hour < right.hour || (hour == right.hour && minute < right.minute))return true;
	return false;
}

bool Time::operator>(const Time right)
{
	if (hour > right.hour || (hour == right.hour && minute > right.minute))return true;
	return false;
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

TableElement* TimeTable::shortestPath(int start, int end, int day, int &transfer_times)
{
	//TODO
	return nullptr;
}

TimeTable::~TimeTable() {};

void priority_queue::pop()
{
	delete[] &(e[1]);
	e[1] = queueelem(e[count]);
	e[count].initialized = false;
	count--;
	int index = 1, index2, index3;
	while (true)
	{
		index2 = e[index * 2] < e[index * 2 + 1] ? index * 2 : index * 2 + 1;
		index3 = index2 ^ 1;
		if (e[index] > e[index2])
		{
			swap(index, index2);
			index = index2;
		}
		else if (e[index] > e[index3])
		{
			swap(index, index3);
			index = index3;
		}
		else break;
	}
}

queueelem priority_queue::top()
{
	return e[1];
}

void priority_queue::swap(int idx1, int idx2)
{
	queueelem temp(e[idx1]);
	e[idx1] = e[idx2];
	e[idx2] = temp;
}

void priority_queue::push(int index, int day, Time time)
{
	count++;
	e[count].setelem(index, day, time);
	int index2 = count;
	while (index2 / 2)
	{
		if (e[index2] < e[index2 / 2])
		{
			swap(index2, index2 / 2);
			index2 /= 2;
		}
		else break;
	}
}

#undef min(a,b)

void queueelem::setelem(int index, int day, Time time)
{
	initialized = true;
	this->index = index;
	this->day = day;
	this->time.setTime(time.hour, time.minute);
}

bool queueelem::operator<(const queueelem right)
{
	if (day < right.day || (day == right.day && time < right.time))return true;
	return false;
}

bool queueelem::operator>(const queueelem right)
{
	if (day > right.day || (day == right.day && time > right.time))return true;
	return false;
}
