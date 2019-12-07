#ifndef __MAP_H__
#define __MAP_H__

#include "CommonHeader.h"

class Node {
public:
	char name;
	int loc_x;
	int loc_y;
};
class Map {
private:
	Node cities[26]; //26 Nodes
	int adj[26][26]; //if 1, edge exist,if 0 no edge
	int edge[26][26]; //distance between cities
public:
	Map();
	char getVertex(int i);
	int getEdge(int i, int j);
	void setEdge(int i, int j);
	void init();
	void reset();
};
#endif