#ifndef GRAPHMAP_H
#define GRAPHMAP_H

#include "PheroKey.h"
#include <vector>
#include <memory>

class GraphMap
{
private:
	int width; // Width of the grid
	int height; // Height of the grid
	float evap_rate = 0.5; //Evapouration Rate
	double DefaultPhero = 10.0; //Default pheromone number MUST NOT BE ZERO
	std::vector<std::shared_ptr<PheroKey>> PheroTable;
	int StartX = -1; //Initial Start Node X-Coordinate
	int StartY = -1; //Initial Start Node Y-Coordinate
	int EndX = -1; //Initial End Node X-Coordinate
	int EndY = -1; //Initial End Node Y-Coordinate
	double MinPhero = 0.000005;
	double MaxPhero = 10;
	std::vector<std::shared_ptr<PheroKey>> BestPathSoFar;
	std::vector<std::shared_ptr<PheroKey>> BestPathOfIter;


public:
	GraphMap(); //Default constructor
	GraphMap(const int n_width,const int n_height); //Parameterized Constructor
	~GraphMap(); //Destructor
	GraphMap( const GraphMap& gMap2);
	std::vector<std::shared_ptr<PheroKey>> GetPheroTable() const; //Returns the pheromone table
	double GetPhero(const int x1, const int y1, const int x2, const int y2) const; //Get pheromone count of a certain position
	double GetPhero(const PheroKey& key) const;
	int GetStartX(); //Return position of Start Node
	int GetStartY();
	int GetEndX(); //Return position of End Node
	int GetEndY();
	std::vector<std::shared_ptr<PheroKey>> GetBestPathOfIter();
    std::vector<std::shared_ptr<PheroKey>> GetBestPathSoFar();
	void PrintStateGrid(); //Prints the State Grid
	void PrintPheroTable(); //Print the Pheromone Table
	void PrintPheroTable(std::vector<std::shared_ptr<PheroKey>> p_map); //Print the Pheromone Table
	void AddEdge(const int x1, const int y1, const int x2, const int y2); //Adds Node to Pheronmone Table
	void AddEdge(const PheroKey& key); //Adds Node to Pheronmone Table
	void UpdatePhero(int iter_number);
	void EvapouratePhero(const double value); //Evapourates Table by specified evapouration value
	void EvapouratePhero();//Evapourates Table by default evapouration value
	std::vector<std::shared_ptr<PheroKey>> GetAllEdges(const int x1, const int y1); //Gets all edges around a point
	void SetStartNode(const int x, const int y); //Sets the start node
	void SetEndNode(const int x, const int y); //Sets the end node
	void RemoveEdge(const PheroKey& key); //Removes edge from PheroTable
	void SetBestPath(std::vector<std::shared_ptr<PheroKey>> BestPath);
	void SetEvapourationRate(double NewRate);
	void StartOver();
};
#endif
