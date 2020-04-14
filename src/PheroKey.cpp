#include "PheroKey.h"

using namespace std;

PheroKey::PheroKey(){
 x1 = y1 = x2 = y2 = 0;	
}


PheroKey::PheroKey(const int x1_n, const int y1_n, const int x2_n, const int y2_n){
	x1 = x1_n;
	y1 = y1_n;
	x2 = x2_n;
	y2 = y2_n;
}

PheroKey::PheroKey( const PheroKey& key2){
	 x1 = key2.x1;
	 y1 = key2.y1;
	 x2 = key2.x2;
	 y2 = key2.y2;
}

int* PheroKey::GetPoint1() const{
	int* p1 = new int[2];
	p1[0] = x1;
	p1[1] = y1;
	return p1;
}

int* PheroKey::GetPoint2() const{
	int* p2 = new int[2];
	p2[0] = x2;
	p2[1] = y2;
	return p2;
}

double PheroKey::GetDistanceBetweenPoints() const{
	return sqrt( (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

bool PheroKey::operator==(const PheroKey& key) const{
	if((this->x1 == key.x1 && this->y1 == key.y1 && this->x2 == key.x2 && this->y2 == key.y2) || (this->x1 == key.x2 && this->y1 == key.y2 && this->x2 == key.x1 && this->y2 == key.y1)){
	return true;
	} else {
	return false;
	}
}

ostream& operator<<(ostream& out, const PheroKey& key){
	return out << "((" << key.x1 << "," << key.y1 << "),(" << key.x2 << "," << key.y2 << "))";
}

bool PheroKey::operator < (const PheroKey& key) const{
	double dis1 = sqrt((this->x1 * this->x1) + (this->y1 * this->y2));
	double dis2 = sqrt((this->x2 * this->x2) + (this->y2 * this->y2));
	double Dis1 = ((dis1 + dis2)/2);
	double dis3 = sqrt((key.x1 * key.x1) + (key.y1 * key.y1));
	double dis4 = sqrt((key.x2 * key.x2) + (key.y2 * key.y2));
	double Dis2 = ((dis3 + dis4)/2);
	if(Dis1 < Dis2){
	return true;
	}else{
	return false;
	}
}

PheroKey::~PheroKey(){
}
