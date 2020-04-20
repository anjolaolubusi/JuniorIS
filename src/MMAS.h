#ifndef MMAS_H
#define MMAS_H

#include "Ant.h"

class MMAS{
private:
	GraphMap graphMap;
	std::vector<Ant> ants;
	int ant_count = 10;
	bool StartHasBeenSet = false;
	bool EndHasBeenSet = false;

public:
	MMAS();
	MMAS(int startX, int startY, int endX, int endY, int number_of_ants);
	MMAS( const MMAS& otherAnt);
	void AddEdge(const int x1, const int y1, const int x2, const int y2);
	void AddEdge(const PheroKey& key);
	void RemoveEdge(const PheroKey& key);
	void SetStartNode(const int x, const int y);
	void SetEndNode(const int x, const int y);
	void SetNumberOfAnts(const int number_of_ants);
	void PrintPheroTable();
	void PrintStateGrid();
	void StartAlgorithm();
	~MMAS();
};

#endif
