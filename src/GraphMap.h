#ifndef ANTMAP_H
#define ANTMAP_H
#include <iostream>
#include <string.h>
#include <map>
#include "PheroKey.h"
#include <set>

class GraphMap
{
private:
	int width; // Width of the grid
	int height; // Height of the grid
	std::string** state_map; // 2 Dimenioal Array of states
	float evap_rate; //Evapouration Rate
	std::map<PheroKey, double> PheroTable;
	double DefaultPhero = 1;
	int StartNodePos[2];
	int EndNodePos[2];

public:
	GraphMap(); //Default constructor
	GraphMap(const int n_width,const int n_height); //Parameterized Constructor
	~GraphMap(); //Destructor
	std::string** GetStateArray() const; //Returns the Array
	std::string GetState(const int x, const int y) const; // Returns the state of (x,y)
	std::map<PheroKey, double> GetPheroTable() const;
	double GetPhero(const int x1, const int y1, const int x2, const int y2) const;
	void PrintStateGrid();
	void PrintPheroTable();
	void AddNode(const int x1, const int y1, const int x2, const int y2);
	void ChangeState(const int x, const int y, const std::string new_state);
	void UpdatePhero(const int x1, const int y1, const int x2, const int y2,const double value);
	std::set<PheroKey> GetAllEdges(const int x1, const int y1);
	void SetStartNode(const int x, const int y);
	void SetEndNode(const int x, const int y);
};
#endif
