#ifndef GRAPHMAP_H
#define GRAPHMAP_H

#include <string.h>
#include <unordered_map>
#include "PheroKey.h"
#include "PheroKeyHash.h"
#include <set>

class GraphMap
{
private:
	int width; // Width of the grid
	int height; // Height of the grid
	std::string** state_map; // 2 Dimenioal Array of states
	float evap_rate = 0.5; //Evapouration Rate
	std::unordered_map<PheroKey, double, PheroKeyHash> PheroTable; //Map object that represents the pheromone count of all the edges of the graph
	double DefaultPhero = 1.0; //Defualt pheromone number MUST NOT BE ZERO
	std::pair<int,int> StartNodePos; //Object for the position of the starting node
	std::pair<int,int> EndNodePos; //Object for the position of the ending node

public:
	GraphMap(); //Default constructor
	GraphMap(const int n_width,const int n_height); //Parameterized Constructor
	~GraphMap(); //Destructor
	std::string** GetStateArray() const; //Returns the State Array
	std::string GetState(const int x, const int y) const; // Returns the state of (x,y)
	std::unordered_map<PheroKey, double, PheroKeyHash> GetPheroTable() const; //Returns the pheromone table
	double GetPhero(const int x1, const int y1, const int x2, const int y2) const; //Get pheromone count of a certain position
	double GetPhero(const PheroKey key) const;
	std::pair<int, int> GetStartNode(); //Return position of Start Node
	std::pair<int, int> GetEndNode(); //Return position of End Node
	void PrintStateGrid(); //Prints the State Grid
	void PrintPheroTable(); //Print the Pheromone Table
	void PrintPheroTable(std::unordered_map<PheroKey, double, PheroKeyHash> p_map); //Print the Pheromone Table
	void AddNode(const int x1, const int y1, const int x2, const int y2); //Adds Node to Pheronmone Table
	void ChangeState(const int x, const int y, const std::string new_state); //Changes State of position
	void UpdatePhero(const int x1, const int y1, const int x2, const int y2,const double value); //Changes pheromone count of variable
	void UpdatePhero(const PheroKey key, const double value); //Changes pheromone count of variable
	void EvapouratePhero(const double value);
	void EvapouratePhero();
	std::unordered_map<PheroKey, double, PheroKeyHash> GetAllEdges(const int x1, const int y1); //Gets all edges around a point 
	void SetStartNode(const int x, const int y); //Sets the start node
	void SetEndNode(const int x, const int y); //Sets the end node
	std::set<PheroKey> FindBestPathOfIter();
};
#endif
