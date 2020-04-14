#ifndef PHEROKEY_H
#define PHEROKEY_H

#include <iostream>
#include <cmath>

class PheroKey{
public:
	PheroKey(); //Default Constructor
	PheroKey(const int x1, const int y1, const int x2, const int y2); //Parameterized Constructor
	PheroKey( const PheroKey& otherkey); //Copy Constructor
	int* GetPoint1() const; //Returns Point1
	int* GetPoint2() const; //Returns Point2
	double GetDistanceBetweenPoints() const; //Returns distance between points
	bool operator ==(const PheroKey& key2) const; //Operator overloader
	friend std::ostream& operator<<(std::ostream& out, const PheroKey& key); //Output overloader
	bool operator < (const PheroKey& key) const; //Operator overloader
	~PheroKey();
	int x1;
	int y1;
	int x2;
	int y2;
};

#endif
