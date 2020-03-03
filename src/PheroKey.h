#ifndef PHEROKEY_H
#define PHEROKEY_H
#include <iostream>
#include <utility>
#include <cmath>

class PheroKey{
private:
	std::pair<int , int> Point1;
	std::pair<int, int> Point2;
public:
	PheroKey();
	PheroKey(std::pair<int, int>p1, std::pair<int, int> p2);
	PheroKey(const int x1, const int y1, const int x2, const int y2);
	PheroKey( const PheroKey& otherkey);
	std::pair<int, int> GetPoint1() const;
	std::pair<int, int> GetPoint2() const;
	double GetDistanceBetweenPoints();
	bool operator ==(const PheroKey& key2);
	friend std::ostream& operator<<(std::ostream& out, const PheroKey& key);
	bool operator < (const PheroKey& key) const;
};

#endif
