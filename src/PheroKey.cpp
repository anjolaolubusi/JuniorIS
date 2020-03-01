#include <iostream>
#include "PheroKey.h"
#include <utility>

using namespace std;

PheroKey::PheroKey(){
	pair<int, int> p1;
	pair<int, int> p2;
	Point1 = p1;
	Point2 = p2;
}

PheroKey::PheroKey(pair<int, int>p1, pair<int, int> p2){
	Point1 = p1;
	Point2 = p2;
}

PheroKey::PheroKey( const PheroKey& key2){
	Point1 = key2.Point1;
	Point2 = key2.Point2;
}

pair<int, int> PheroKey::GetPoint1() const{
	return this->Point1;
}

pair<int, int> PheroKey::GetPoint2() const{
	return this->Point2;
}

bool PheroKey::operator==(const PheroKey& key){
	if((Point1 == key.GetPoint1() && Point2 == key.GetPoint2()) || (this->Point1 == key.GetPoint2() && this->Point2 == key.GetPoint1())){
	return true;
	} else {
	return false;
	}
}

ostream& operator<<(ostream& out, const PheroKey& key){
	return out << "((" << key.GetPoint1().first << "," << key.GetPoint1().second << "),(" << key.GetPoint2().first << "," << key.GetPoint2().second << "))";
}
