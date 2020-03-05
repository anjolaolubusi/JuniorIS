#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <string.h>
#include "PheroKey.h"
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>

class Ant{
private:
	int x; // x position
	int y; // y position
	std::set<PheroKey> nodes_visited; // Set of Node Visitied
	std::string state = "A"; //String containing state

public:
	Ant(); //Default constructor
	Ant(const int x, const int y); // Parameterized constructor
	Ant(std::pair<int, int>p1); // Parameterized constructor
	Ant(const Ant& anthony); // Copy Constructor
	int GetX() const; //Returns x position
	int GetY() const; //Returns y position
	std::set<PheroKey> GetNodesVisited();
	void SetX(const int new_x); //Sets the x position
	void SetY(const int new_y); //Sets the y position
	void MoveAnt(std::set<PheroKey> SAPE, std::map<PheroKey, double> pheroMap); //Moves the ant
	void PrintVistedNodes();
	friend std::ostream& operator<<(std::ostream& out, const Ant anthony); //Output overloader
};
#endif
