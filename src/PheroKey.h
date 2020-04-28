#ifndef PHEROKEY_H
#define PHEROKEY_H

#include <iostream>
#include <cmath>

class PheroKey{
public:
	PheroKey(); //Default Constructor
	PheroKey(const int x1, const int y1, const int x2, const int y2, const double pCount); //Parameterized Constructor
	PheroKey( const PheroKey& otherkey); //Copy Constructor
	void UpdatePhero(double NewPheroCount) const;
	void ReplacePhero(double NewPheroCount) const;
	double GetDistanceBetweenPoints() const; //Returns distance between points
	int GetX1() const; //Returns x-coordinate of first point
	int GetX2() const; //Returns y-coordinate of first point
	int GetY1() const; //Returns x-coordinate of second point
	int GetY2() const; //Returns y-coordinate of second point
	double GetPhero() const; //Returns pheromone value of edge
	bool operator ==(const PheroKey& key2) const; //Operator overloader
	friend std::ostream& operator<<(std::ostream& out, const PheroKey& key); //Output overloader
	bool operator < (const PheroKey& key) const; //Operator overloader
	~PheroKey(); //Destructor
	void SetDisBetweenPoint(const double NewDis);
	void ResetDisBetweenPoint(); //Resets the Distance Between Points
	bool GetWalkableState() const; //Returns if the edge is walkable
	void SetWalkableState(bool newState); //Returns sets if the edge walkable
private:
	int x1; //X Coordinate of First Point
	int y1; //Y Coordinate of First Point
	int x2; //X Coordinate of Second Point
	int y2; //Y Coordinate of Second Point
    mutable double pheroCount; //Pheromone value of the edge
	double DisBetweenPoints; //Distance between vertecies of edge
	bool IsWalkable = true; //Boolean to determine if edge is walkable
};

#endif
