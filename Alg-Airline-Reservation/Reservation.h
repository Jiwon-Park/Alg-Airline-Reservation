#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include "CommonHeader.h"
#include "timetable.h"

typedef enum { BLACK, RED }rbcolor;
typedef enum { FIRST, BUSINESS, ECONOMY }seatlevel;
class Reservation;

class Data
{
private:
	string name;
	int res_num;
	char source;
	char dest;
	Time departure;
	int departure_date;
	Time arrival;
	int arrival_date;
	TableElement* transfer_list;
	int transfer_times;
	seatlevel level;
	int price;
	int flight_time;

	friend class Reservation;
	friend class Node;
public:
	Data(string name, int res_num, char source, char dest,
		Time departure, int departure_date, Time arrival, int arrival_date,
		TableElement* transfer_list, int transfer_times, seatlevel level, int price, int flight_time);

	void showInfo(void);

	~Data(void);
};

class Node
{
private:
	Data * data;
	rbcolor color;
	Node* left;
	Node* right;
	Node* parent;

	friend class Reservation;
	friend class AirlineHandler;
public:
	Node(void);
	Node(Data& input, Node* parent, Node* left, Node* right, rbcolor color);

	~Node(void);
};

class Reservation
{
private:
	Node * root;
	Node* nil;
	int num_of_reserv;

private:
	void left_rotate(Node* target);
	void right_rotate(Node* target);

	Node* successor(Node* target);

	void insert_fixup(Node* cur);
	void delete_fixup(Node* x);

	void destroy_nodes(Node* n);

public:
	Reservation(void);

	Node* reservation_search(int num);
	bool reservation_insert(Data& input);
	bool reservation_delete(int res_num);

	~Reservation(void);
};
#endif