#ifndef GRAPHMAP_H
#define GRAPHMAP_H

#include "PheroKey.h"
#include <vector>
#include <memory>
#include <random>
#include <string>

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
	double MinPhero = 0.000005; //Minimum pheromone value
	double MaxPhero = 10; //Maximum pheromone value
	double SnowProb = 0.5; //Probability of an edge being blocked
	std::vector<std::shared_ptr<PheroKey>> BestPathSoFar;  //Object that represent of the best path so far
	std::vector<std::shared_ptr<PheroKey>> BestPathOfIter; //Object that represent of the best path of the iteration


public:
	GraphMap(); //Default constructor
	GraphMap(const int n_width,const int n_height); //Parameterized Constructor
	~GraphMap(); //Destructor
	GraphMap( const GraphMap& gMap2); //Copy Constructor
	std::vector<std::shared_ptr<PheroKey>> GetPheroTable() const; //Returns the pheromone table
	double GetPhero(const int x1, const int y1, const int x2, const int y2) const; //Get pheromone count of a certain position
	double GetPhero(const PheroKey& key) const; //Get pheromone count of a certain key
	int GetStartX(); //Return x-coordinate of Start Node
	int GetStartY(); //Return y-coordinate of Start Node
	int GetEndX(); //Return x-coordinate of End Node
	int GetEndY(); //Return y-coordinate of End Node
	double GetMaxOfPheroTable() const; //Gets Maximum pheromone value of the edges
	double GetMaxPhero() const; //Get maximum pheromone value;
	std::vector<std::shared_ptr<PheroKey>> GetBestPathOfIter(); //Returns the best path so far
    std::vector<std::shared_ptr<PheroKey>> GetBestPathSoFar(); //Returns the best path of the iteration
	void PrintPheroTable(); //Print the Pheromone Table
	void PrintPheroTable(std::vector<std::shared_ptr<PheroKey>> p_map); //Print the Pheromone Table
	void AddEdge(const int x1, const int y1, const int x2, const int y2); //Adds Node to Pheromone Table
	void AddEdge(const PheroKey& key); //Adds Node to Pheromone Table
	void UpdatePhero(int iter_number); //Update Pheromone Table
	void EvapouratePhero(const double value); //Evapourates Table by specified evapouration value
	void EvapouratePhero();//Evapourates Table by default evapouration value
	std::vector<std::shared_ptr<PheroKey>> GetAllEdges(const int x1, const int y1); //Gets all edges around a point
	void SetStartNode(const int x, const int y); //Sets the start node
	void SetEndNode(const int x, const int y); //Sets the end node
	void RemoveEdge(const PheroKey& key); //Removes edge from PheroTable
	void SetBestPath(std::vector<std::shared_ptr<PheroKey>> BestPath); //Sets the best path
	void SetEvapourationRate(double NewRate); //Sets the evapouration rate
	void StartOver(); //Resets the pheromone table
	void SetSnowProb(double newProb); //Sets blocked edge probability
	double GetSnowProb() const; //Get blocked edge probability
	void CanadianSnow(); //Blocks edges
	bool GetWalkable(int x1, int y1, int x2, int y2) const; //Returns walkable state
	void MakeGraphWalkable(); //Makes whole graph walkable
	void ClearBestPath(); //Clear best path
	void ResetPheromoneTable(); //Resets Pheromone Table
};
#endif
