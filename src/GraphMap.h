#ifndef GRAPHMAP_H
#define GRAPHMAP_H

#include <string.h>
#include "PheroKey.h"
#include <vector>

class GraphMap
{
private:
	int width; // Width of the grid
	int height; // Height of the grid
	std::string** state_map; // 2 Dimensional Array of states
	float evap_rate = 0.5; //Evapouration Rate
	double DefaultPhero = 1.0; //Default pheromone number MUST NOT BE ZERO
	std::vector<PheroKey> PheroTable;
	int StartX = -1; //Initial Start Node X-Coordinate
	int StartY = -1; //Initial Start Node Y-Coordinate
	int EndX = -1; //Initial End Node X-Coordinate
	int EndY = -1; //Initial End Node Y-Coordinate

public:
	GraphMap(); //Default constructor
	GraphMap(const int n_width,const int n_height); //Parameterized Constructor
	~GraphMap(); //Destructor
	GraphMap( const GraphMap& gMap2);
	std::string** GetStateArray() const; //Returns the State Array
	std::string GetState(const int x, const int y) const; // Returns the state of (x,y)
	std::vector<PheroKey> GetPheroTable() const; //Returns the pheromone table
	double GetPhero(const int x1, const int y1, const int x2, const int y2) const; //Get pheromone count of a certain position
	double GetPhero(const PheroKey& key) const;
	int GetStartX(); //Return position of Start Node
	int GetStartY();
	int GetEndX(); //Return position of End Node
	int GetEndY();
	void PrintStateGrid(); //Prints the State Grid
	void PrintPheroTable(); //Print the Pheromone Table
	void PrintPheroTable(std::vector<PheroKey> p_map); //Print the Pheromone Table
	void AddNode(const int x1, const int y1, const int x2, const int y2); //Adds Node to Pheronmone Table
	void ChangeState(const int x, const int y, const std::string new_state); //Changes State of position
	void UpdatePhero(const int x1, const int y1, const int x2, const int y2,const double value); //Changes pheromone count of variable
	void UpdatePhero(const PheroKey key, double value); //Changes pheromone count of variable
	void EvapouratePhero(const double value); //Evapourates Table by specified evapouration value
	void EvapouratePhero();//Evapourates Table by default evapouration value
	std::vector<PheroKey> GetAllEdges(const int x1, const int y1); //Gets all edges around a point
	void SetStartNode(const int x, const int y); //Sets the start node
	void SetEndNode(const int x, const int y); //Sets the end node
	void RemoveEdge(const PheroKey& key); //Removes edge from PheroTable
};
#endif
