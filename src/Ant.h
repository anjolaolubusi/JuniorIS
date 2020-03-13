#ifndef ANT_H
#define ANT_H

#include <iostream>
#include "GraphMap.h"
#include <random>

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
	void MoveAntToEndNode(GraphMap& gmap, bool first_run=false); //Moves the ant
	void MoveAntToStartNode(GraphMap& gmap);
	bool IsAtNode(const int n_x, const int n_y);
	bool IsOnKey(const PheroKey& key);
	void EmptyNV();
	void PrintVistedNodes();
	friend std::ostream& operator<<(std::ostream& out, const Ant anthony); //Output overloader
};
#endif
