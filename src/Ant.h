#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <string.h>
#include "PheroKey.h"
#include <set>
#include <map>
#include <algorithm>
#include <vector>

class Ant{
private:
	int x;
	int y;
	std::set<PheroKey> nodes_visited;
	std::string state = "A";

public:
	Ant();
	Ant(const int x, const int y);
	int GetX() const;
	int GetY() const;
	void SetX(const int new_x);
	void SetY(const int new_y);
	void MoveAnt(std::set<PheroKey> SAPE, std::map<PheroKey, double> pheroMap);
};
#endif
