#ifndef PHEROKEY_H
#define PHEROKEY_H

#include <iostream>
#include <utility>
#include <cmath>

class PheroKey{
private:
	std::pair<int , int> Point1; //First coordinate
	std::pair<int, int> Point2; //Second coordinate
public:
	PheroKey(); //Default Constructor
	PheroKey(std::pair<int, int>p1, std::pair<int, int> p2); //Parameterized Constructor
	PheroKey(const int x1, const int y1, const int x2, const int y2); //Parameterized Constructor
	PheroKey( const PheroKey& otherkey); //Copy Constructor
	std::pair<int, int> GetPoint1() const; //Returns Point1
	std::pair<int, int> GetPoint2() const; //Returns Point2
	double GetDistanceBetweenPoints() const; //Returns distance between points
	bool operator ==(const PheroKey& key2) const; //Operator overloader
	friend std::ostream& operator<<(std::ostream& out, const PheroKey& key); //Output overloader
	bool operator < (const PheroKey& key) const; //Operator overloader
};

#endif
