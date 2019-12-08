#ifndef __MAP_H__
#define __MAP_H__

#include "CommonHeader.h"

class MapNode {
public:
	char name;
	int loc_x;
	int loc_y;
};
class Map {
private:
	MapNode cities[26]; //26 Nodes
	int adj[26][26]; //if 1, edge exist,if 0 no edge
	int edge[26][26]; //distance between cities
public:
	Map();
	char getVertex(int i) const;
	int getEdge(int i, int j) const;
	void setEdge(int i, int j);
	void init();
	void reset();
};
#endif