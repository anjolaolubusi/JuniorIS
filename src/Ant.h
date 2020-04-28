#ifndef ANT_H
#define ANT_H

#include <iostream>
#include "GraphMap.h"
#include <SFML/Graphics.hpp>


class Ant{
private:
	int ant_x; // x position
	int ant_y; // y position
	std::vector<std::shared_ptr<PheroKey>> keys_visited; // Set of Node Visitied
	std::string state = "A"; //String containing state
	sf::RectangleShape shape; //Visual representative of ant
	double moveSpeed; //Movement speed
	float ant_slope = 0;
	float UnitVecX; //X coordinate of destination unit vector
	float UnitVecY; //Y coordinate of destination unit vector
	float VecMag; //Magnitude of vector
	bool isFin = false; //boolean variable that represents if ant is finished moving across the graph

public:
	Ant(); //Default constructor
	Ant(const int x, const int y); // Parameterized constructor
	Ant(const Ant& anthony); // Copy Constructor
	int GetX() const; //Returns x position
	int GetY() const; //Returns y position
	double GetPheroCount(GraphMap& gmap); //Gets pheromone count of path travelled
	double GetValueOfPath() const; //Gets heuristic value of path
	std::vector<std::shared_ptr<PheroKey>> GetKeysVisited() const; //Returns path travelled
	void SetX(const int new_x); //Sets the x position
	void SetY(const int new_y); //Sets the y position
	void MoveAntToEndNode(GraphMap& gmap, bool first_run=false); //Moves the ant to end node
	void MoveAntToStartNode(GraphMap& gmap); //Moves the ant to the start node
	bool IsAtNode(const int n_x, const int n_y); //Check if the ant is at a certain node
	bool IsOnKey(const PheroKey& key); //Check if ant is on key
	void EmptyKV(); //Empties the node visited vector
	void PrintVistedKeys() const; //Prints travelled path
	friend std::ostream& operator<<(std::ostream& out, const Ant& anthony); //Output overloader
	void PrintAntInfo(GraphMap& gmap) const; //Prints the ant object with the proper pheromone count
	~Ant();

	void update(const float& dt); //Updates ant's graphical position
	void render(sf::RenderTarget* target);
	void moveX();
	void moveY();

	bool GraphAntAtNode();
	bool GraphAntAtNode(int x, int y);
	void SetSpeed(double speed);
	bool IsAntFin();
	bool IsPathWalkable();
};
#endif
