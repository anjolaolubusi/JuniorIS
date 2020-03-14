#include "PheroKey.h"

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

PheroKey::PheroKey(const int x1, const int y1, const int x2, const int y2){
	Point1.first = x1;
	Point1.second = y1;
	Point2.first = x2;
	Point2.second = y2;
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

double PheroKey::GetDistanceBetweenPoints() const{
	return sqrt( pow((Point2.first - Point1.first), 2.0) + pow((Point2.second - Point1.second), 2));
}

bool PheroKey::operator==(const PheroKey& key) const{
	if((this->Point1 == key.GetPoint1() && this->Point2 == key.GetPoint2()) || (this->Point1 == key.GetPoint2() && this->Point2 == key.GetPoint1())){
	return true;
	} else {
	return false;
	}
}

ostream& operator<<(ostream& out, const PheroKey& key){
	return out << "((" << key.GetPoint1().first << "," << key.GetPoint1().second << "),(" << key.GetPoint2().first << "," << key.GetPoint2().second << "))";
}

bool PheroKey::operator < (const PheroKey& key) const{
	double dis1 = sqrt((this->Point1.first * this->Point1.first) + (this->Point1.second * this->Point1.second));
	double dis2 = sqrt((this->Point2.first * this->Point2.first) + (this->Point2.second * this->Point2.second));
	double Dis1 = ((dis1 + dis2)/2);
	double dis3 = sqrt((key.GetPoint1().first * key.GetPoint1().first) + (key.GetPoint1().second * key.GetPoint1().second));
	double dis4 = sqrt((key.GetPoint2().first * key.GetPoint2().first) + (key.GetPoint2().second * key.GetPoint2().second));
	double Dis2 = ((dis3 + dis4)/2);
	if(Dis1 < Dis2){
	return true;
	}else{
	return false;
	}
}
