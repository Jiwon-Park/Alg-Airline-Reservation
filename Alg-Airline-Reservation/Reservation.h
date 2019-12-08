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
	Time flight_time;

	friend class Reservation;
	friend class TreeNode;
public:
	Data(string name, int res_num, char source, char dest,
		Time departure, int departure_date, Time arrival, int arrival_date,
		TableElement* transfer_list, int transfer_times, seatlevel level, int price, Time& flight_time);

	void showInfo(void);

	~Data(void);
};

class TreeNode
{
private:
	Data * data;
	rbcolor color;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	friend class Reservation;
	friend class AirlineHandler;
public:
	TreeNode(void);
	TreeNode(Data& input, TreeNode* parent, TreeNode* left, TreeNode* right, rbcolor color);

	~TreeNode(void);
};

class Reservation
{
private:
	TreeNode * root;
	TreeNode* nil;
	int num_of_reserv;

private:
	void left_rotate(TreeNode* target);
	void right_rotate(TreeNode* target);

	TreeNode* successor(TreeNode* target);

	void insert_fixup(TreeNode* cur);
	void delete_fixup(TreeNode* x);

	void destroy_nodes(TreeNode* n);

public:
	Reservation(void);

	TreeNode* reservation_search(int num);
	TreeNode* reservation_insert(Data& input);
	bool reservation_delete(int res_num);

	~Reservation(void);
};
#endif