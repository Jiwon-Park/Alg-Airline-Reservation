#include "Reservation.h"

Data::Data(string name, int res_num, char source, char dest,
	Time departure, int departure_date, Time arrival, int arrival_date,
	TableElement* transfer_list, int transfer_times, seatlevel level, int price, Time& flight_time)

	: name(name), res_num(res_num), source(source), dest(dest),
	departure(departure), departure_date(departure_date), arrival(arrival), arrival_date(arrival_date),
	transfer_list(transfer_list), transfer_times(transfer_times), level(level), price(price), flight_time(flight_time)
{}

void Data::showInfo(void)
{
	cout << "name : " << name << endl;
	cout << "reserv num : " << res_num << endl;
	cout << "source : " << source << endl;
	cout << "destination : " << dest << endl;
	cout << "departure : day " << departure_date << ", " << departure.hour << ":" << departure.minute << endl;
	cout << "arrive : day " << (arrival_date - 1) % 31 + 1 << ", " << arrival.hour << ":" << arrival.minute << endl;
	cout << "flight path" << endl;
	for (int i = 0; i < transfer_times; i++)
		transfer_list[i].showInfo();
	cout << "flight time : " << flight_time.hour << "hours " << flight_time.minute << "minutes" << endl;
	cout << "seat level : ";
	if (level == ECONOMY)
		cout << "economy" << endl;
	else if (level == BUSINESS)
		cout << "business" << endl;
	else
		cout << "first" << endl;
	cout << "price : " << price << endl;
}

Data::~Data(void)
{
	delete[] transfer_list;
}

TreeNode::TreeNode(void)
	: data(NULL), color(BLACK), left(NULL), right(NULL), parent(NULL)
{}
TreeNode::TreeNode(Data& input, TreeNode* parent, TreeNode* left, TreeNode* right, rbcolor color)
	: parent(parent), left(left), right(right), color(color)
{
	data = new Data(input);
}

TreeNode::~TreeNode(void)
{
	delete data;
}


void Reservation::left_rotate(TreeNode* target)
{
	TreeNode* r = target->right;
	target->right = r->left;

	if (r->left != nil)
		r->left->parent = target;

	r->parent = target->parent;

	if (target->parent == nil)
		root = r;
	else if (target == target->parent->left)
		target->parent->left = r;
	else
		target->parent->right = r;

	r->left = target;
	target->parent = r;
}

void Reservation::right_rotate(TreeNode* target)
{
	TreeNode* l = target->left;
	target->left = l->right;

	if (l->right != nil)
		l->right->parent = target;

	l->parent = target->parent;
	if (target->parent == nil)
		root = l;
	else if (target == target->parent->left)
		target->parent->left = l;
	else
		target->parent->right = l;

	l->right = target;
	target->parent = l;
}

TreeNode* Reservation::reservation_search(int num)
{
	TreeNode* cur = root;
	while (cur != nil) {
		if (cur->data->res_num == num)
			break;
		else if (cur->data->res_num < num)
			cur = cur->right;
		else
			cur = cur->left;
	}

	return cur;
}

TreeNode* Reservation::successor(TreeNode* target)
{
	TreeNode* result = NULL;
	if (target->right != nil) {
		result = target->right;
		while (result->left != nil)
			result = result->left;
	}
	else {
		result = target->parent;
		while (result != nil && result->right == target) {
			target = result;
			result = result->parent;
		}
	}

	return result;
}

void Reservation::insert_fixup(TreeNode* cur)
{
	TreeNode* uncle = NULL;

	while (cur->parent->color == RED) {
		if (cur->parent == cur->parent->parent->left) {
			uncle = cur->parent->parent->right;
			if (uncle->color == RED) {
				uncle->color = BLACK;
				cur->parent->color = BLACK;
				cur->parent->parent->color = RED;
				cur = cur->parent->parent;
			}
			else {
				if (cur == cur->parent->right) {
					cur = cur->parent;
					left_rotate(cur);
				}
				cur->parent->color = BLACK;
				cur->parent->parent->color = RED;
				right_rotate(cur->parent->parent);
			}
		}
		else {
			uncle = cur->parent->parent->left;
			if (uncle->color == RED) {
				uncle->color = BLACK;
				cur->parent->color = BLACK;
				cur->parent->parent->color = RED;
				cur = cur->parent->parent;
			}
			else {
				if (cur == cur->parent->left) {
					cur = cur->parent;
					right_rotate(cur);
				}
				cur->parent->color = BLACK;
				cur->parent->parent->color = RED;
				left_rotate(cur->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

void Reservation::delete_fixup(TreeNode* x)
{
	TreeNode* w = NULL;
	TreeNode* root = this->root;
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				if (root != this->root) root = this->root;
				w = x->parent->right;
			}

			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					right_rotate(w);
					if (root != this->root) root = this->root;
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(x->parent);
				x = root;
			}
		}
		else {
			w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent);
				if (root != this->root) root = this->root;
				w = x->parent->left;
			}

			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(w);
					if (root != this->root) root = this->root;
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

void Reservation::destroy_nodes(TreeNode* n)
{
	if (n != nil) {
		destroy_nodes(n->left);
		destroy_nodes(n->right);
		delete n;
	}
}

Reservation::Reservation(void)
	: num_of_reserv(0)
{
	nil = new TreeNode;
	root = nil;
}

TreeNode* Reservation::reservation_insert(Data& input)
{
	int num = input.res_num;
	TreeNode* cur_parent = nil;
	TreeNode* cur = root;
	TreeNode* newnode = NULL;

	while (cur != nil) {
		cur_parent = cur;
		if (num == cur->data->res_num) {
			cout << "Reservation number is duplicated." << endl;
			return NULL;
		}
		else if (num < cur->data->res_num) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	newnode = new TreeNode(input, cur_parent, nil, nil, RED);

	if (cur_parent == nil) {
		root = newnode;
	}
	else if (num < cur_parent->data->res_num) {
		cur_parent->left = newnode;
	}
	else {
		cur_parent->right = newnode;
	}

	insert_fixup(newnode);

	return newnode;
}

bool Reservation::reservation_delete(int res_num)
{
	TreeNode* target = reservation_search(res_num);
	TreeNode* y = NULL;
	TreeNode* x = NULL;
	Data* temp = NULL;

	if (target == nil) {
		cout << "Reservation info does not exist" << endl;
		return false;
	}

	if (target->left == nil || target->right == nil)
		y = target;
	else
		y = successor(target);

	if (y->left != nil)
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;

	if (y->parent == nil)
		root = x;
	else {
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	if (y != target) {
		temp = target->data;
		target->data = y->data;
		y->data = temp;
	}

	if (y->color == BLACK)
		delete_fixup(x);

	cout << "Deleted reservation info" << endl;
	y->data->showInfo();
	delete y;
	return true;
}

Reservation::~Reservation(void)
{
	destroy_nodes(root);
	delete nil;
}