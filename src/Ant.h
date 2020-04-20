#ifndef ANT_H
#define ANT_H

#include <iostream>
#include "GraphMap.h"
#include <random>


class Ant{
private:
	int ant_x; // x position
	int ant_y; // y position
	std::vector<std::shared_ptr<PheroKey>> keys_visited; // Set of Node Visitied
	std::string state = "A"; //String containing state

public:
	Ant(); //Default constructor
	Ant(const int x, const int y); // Parameterized constructor
	Ant(const Ant& anthony); // Copy Constructor
	int GetX() const; //Returns x position
	int GetY() const; //Returns y position
	double GetPheroCount(GraphMap& gmap);
	double GetValueOfPath() const;
	std::vector<std::shared_ptr<PheroKey>> GetKeysVisited() const;
	void SetX(const int new_x); //Sets the x position
	void SetY(const int new_y); //Sets the y position
	void MoveAntToEndNode(GraphMap& gmap, bool first_run=false); //Moves the ant to end node
	void MoveAntToStartNode(GraphMap& gmap); //Moves the ant to the start node
	bool IsAtNode(const int n_x, const int n_y); //Check if the ant is at a certain node
	bool IsOnKey(const PheroKey& key); //Check if ant is on key
	void EmptyKV(); //Empties the node visited vector
	void PrintVistedKeys() const;
	friend std::ostream& operator<<(std::ostream& out, const Ant& anthony); //Output overloader
	void PrintAntInfo(GraphMap& gmap) const; //Prints the ant object with the proper pheromone count
	~Ant();
};
#endif
