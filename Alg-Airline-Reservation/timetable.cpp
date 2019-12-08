#include "timetable.h"

TableElement::TableElement() {};

TableElement::TableElement(int s, int e, Time d) 
{
	start = s;
	end = e;
	departure = d;
}

void TableElement::showInfo() const
{
	cout << "Source: " << (char)(start + 'a') << " " << "Destination: " << (char)(end + 'a') << " " << "Departure time: " << departure.hour << ":" << departure.minute << endl;
}

Time::Time() {};

Time:: Time(const Time& ref)
{
	hour = ref.hour;
	minute = ref.minute;
}

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

bool Time::operator<(const Time right) const
{
	if (hour < right.hour || (hour == right.hour && minute < right.minute))return true;
	return false;
}

bool Time::operator>(const Time right) const
{
	if (hour > right.hour || (hour == right.hour && minute > right.minute))return true;
	return false;
}

Time Time::operator+(const Time right) const
{
	Time ret(hour + right.hour, minute + right.minute);
	if (ret.minute >= 60)
	{
		ret.hour++;
		ret.minute -= 60;
	}
	return ret;
}

Time Time::operator+=(const Time right)
{
	hour += right.hour;
	minute += right.minute;
	if (minute >= 60)
	{
		hour++;
		minute -= 60;
	}
	return *this;
}

TimeTable::TimeTable() {};

TimeTable::TimeTable(const Map map)
{
	setTimeTable(map);
}

void TimeTable::setTimeTable(const Map map)
{
	for (size_t i = 0; i < 26; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (map.getEdge(i, j))
			{
				table[0][i * 26 + j].start = i;
				table[0][i * 26 + j].end = j;
				table[0][i * 26 + j].departure.setTime(rand() % 24, rand() % 60);
				table[0][j * 26 + i].start = j;
				table[0][j * 26 + i].end = i;
				table[0][j * 26 + i].departure.setTime(rand() % 24, rand() % 60);

			}

		}
	}
	for (size_t i = 1; i < 31; i++)
	{
		memcpy(table[i], table[0], sizeof(table[0]));
		for (size_t j = 0; j < 1000; j++)
		{
			if(table[i][j].start >= 0)
				table[i][j].departure.setTime(rand() % 24, rand() % 60);
		}
	}
}

void TimeTable::showTimeTable(int day) const
{
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			if (table[day - 1][i * 26 + j].start >= 0)
				table[day - 1][i].showInfo();
		}
	}
}

TableElement TimeTable::getElement(int day, int index) const
{
	return table[day][index];
}

TableElement* TimeTable::getOptimalRoute(int start, int end, int day, const Map map, int& transfer_times, int& arrival_date, Time& departure_time, Time& arrival_time) const
{
	start -= 'a';
	end -= 'a';
	day -= 1;
	transfer_times = 1;
	priority_queue queue;
	queueelem temp, cost[26];
	int dist, hour_consume, min_consume, tday;
	TableElement path[26];
	Time arrival, consume;
	cost[start].setelem(start, day, Time(0, 0));
	queue.push(start, day, Time(0, 0));
	while (!queue.empty())
	{
		temp = queue.front();
		queue.pop();
		for (int i = 0; i < 26; i++)
		{
			if (dist = map.getEdge(temp.index, i))			//temp.index -> i
			{
				tday = temp.day;
				hour_consume = dist / 500;
				min_consume = (dist % 500) * 60 / 500;
				consume.setTime(hour_consume, min_consume);
				if (temp.time > table[tday % 31][temp.index * 26 + i].departure)tday++;				//���ð� ��Ÿ�� ������
				arrival = table[tday % 31][temp.index * 26 + i].departure + consume;				//�ð� ���?
				int arrday = tday + arrival.hour / 24;												//�ϼ� �Ѿ�°� ���?
				arrival.hour = arrival.hour % 24;

				if (!cost[i].initialized || (cost[i].day > arrday || (cost[i].day == arrday && cost[i].time > arrival)))
				{
					cost[i].setelem(i, arrday, arrival);
					queue.push(i, arrday, arrival);
					path[i] = table[tday % 31][temp.index * 26 + i];
				}
			}
		}
	}
	int index = end;
	arrival_date = cost[end].day + 1;
	arrival_time = cost[end].time;
	while (path[index].start != start)
	{
		index = path[index].start;
		transfer_times++;
	}
	TableElement* ret = new TableElement[transfer_times];
	int c = 0;
	index = end;
	while (path[index].start != start)
	{
		c++;
		ret[transfer_times - c] = path[index];
		index = path[index].start;
	}
	ret[transfer_times - c - 1] = path[index];
	departure_time = path[index].departure;
	return ret;
}

TimeTable::~TimeTable() {};

void priority_queue::pop()
{
	if (count == 1)
	{
		e[1].initialized = false;
		count = 0;
		return;
	}
	e[1] = e[count];
	e[count].initialized = false;
	count--;
	int index = 1, index2, index3;
	while (true)
	{
		index2 = e[index * 2] < e[index * 2 + 1] ? index * 2 : index * 2 + 1;
		index3 = index2 ^ 1;
		if (e[index2].initialized && e[index] > e[index2])
		{
			swap(index, index2);
			index = index2;
		}
		else if (e[index3].initialized && e[index] > e[index3])
		{
			swap(index, index3);
			index = index3;
		}
		else break;
	}
}

queueelem priority_queue::front() const
{
	return e[1];
}

bool priority_queue::empty() const
{
	if (count) return false;
	return true;
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

void queueelem::setelem(int index, int day, const Time time)
{
	initialized = true;
	this->index = index;
	this->day = day;
	this->time = time;
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
