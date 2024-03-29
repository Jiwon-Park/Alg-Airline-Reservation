#include "Map.h"

Map::Map() {
	init();
	reset();
}
char Map::getVertex(int i) const {
	//return city name
	return cities[i].name;
}
int Map::getEdge(int i, int j) const {
	//return distance between cities
	return edge[i][j];
}
void Map::setEdge(int i, int j) {
	//calculate distance between cities
	adj[i][j] = 1;
	adj[j][i] = 1;
	edge[i][j] = sqrt(abs(cities[i].loc_x - cities[j].loc_x) * abs(cities[i].loc_x - cities[j].loc_x) 
					+ abs(cities[i].loc_y - cities[j].loc_y) * abs(cities[i].loc_y - cities[j].loc_y));
	edge[j][i] = edge[i][j];
}
void Map::init() {
	//set location of cities
	for (int i = 0; i < 26; i++) {
		cities[i].name = i + 97;
		cities[i].loc_x = rand() % 6001 - 3000;
		cities[i].loc_y = rand() % 6001 - 3000;
		for (int j = 0; j < i; j++) {
			if (cities[i].loc_x == cities[j].loc_x && cities[i].loc_y == cities[j].loc_y) {
				i--;
				break;
			}
		}
	}
}
void Map::reset() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			adj[i][j] = 0;
			edge[i][j] = 0;
		}
	}
	srand(time(NULL));
	//select 100 pair of cities
	for (int i = 0; i < 100; i++) {
		int j = rand() % 26;
		int k = rand() % 26;
		if (j == k || adj[j][k] == 1) {
			i--;
		}
		setEdge(j, k);
	}
}
