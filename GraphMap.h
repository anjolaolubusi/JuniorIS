#ifndef ANTMAP_H
#define ANTMAP_H
#include <iostream>
#include <string.h>

using namespace std;

class GraphMap
{
private:
	int width; // Width of the grid
	int height; // Height of the grid
	int** phero_map; // 2 Dimenional Array of the number of pheromones
	string** state_map; // 2 Dimenioal Array of states
	float evap_rate; //Evapouration Rate

public:
	GraphMap(); //Default constructor
	GraphMap(const int n_width,const int n_height); //Parameterized Constructor
	~GraphMap(); //Destructor
	string** GetStateArray(); //Returns the Array
	string GetState(const int x, const int y); // Returns the state of (x,y)
	int** GetPheroArray(); //Returns the Array
	int GetPhero(const int x, const int y); //Returns the pheromone count
	void PrintPheroGrid();
	void PrintStateGrid();
	void ChangeState(const int x, const int y, const string new_state);
	void ChangePhero(const int x, const int y, const int new_phero);	
};
#endif
