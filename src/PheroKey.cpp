#include "PheroKey.h"

using namespace std;
PheroKey::PheroKey(){
 x1 = y1 = x2 = y2 = -1;
pheroCount = 10;
DisBetweenPoints = 0;
}


/*PheroKey::PheroKey(const int x1_n, const int y1_n, const int x2_n, const int y2_n){
	x1 = x1_n;
	y1 = y1_n;
	x2 = x2_n;
	y2 = y2_n;
	pheroCount = 10;
}*/

PheroKey::PheroKey(const int x1_n, const int y1_n, const int x2_n, const int y2_n, const double pCount){
	x1 = x1_n;
	y1 = y1_n;
	x2 = x2_n;
	y2 = y2_n;
	pheroCount = pCount;
	DisBetweenPoints = sqrt( (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
PheroKey::PheroKey( const PheroKey& key2){
	 x1 = key2.x1;
	 y1 = key2.y1;
	 x2 = key2.x2;
	 y2 = key2.y2;
	 pheroCount = key2.pheroCount;
	 DisBetweenPoints = key2.DisBetweenPoints;
}

void PheroKey::UpdatePhero(double newvalue) const{
	this->pheroCount = this->pheroCount + newvalue;
}


void PheroKey::ReplacePhero(double newvalue) const{
	this->pheroCount = newvalue;
}

double PheroKey::GetDistanceBetweenPoints() const{
	return DisBetweenPoints;
}

int PheroKey::GetX1() const{
	return x1;
}


int PheroKey::GetX2() const{
	return x2;
}

int PheroKey::GetY1() const{
	return y1;
}

int PheroKey::GetY2() const{
	return y2;
}

double PheroKey::GetPhero() const{
	return pheroCount;
}

bool PheroKey::operator==(const PheroKey& key) const{
	if((this->x1 == key.x1 && this->y1 == key.y1 && this->x2 == key.x2 && this->y2 == key.y2) || (this->x1 == key.x2 && this->y1 == key.y2 && this->x2 == key.x1 && this->y2 == key.y1)){
	return true;
	} else {
	return false;
	}
}

ostream& operator<<(ostream& out, const PheroKey& key){
	return out << "((" << key.x1 << "," << key.y1 << "),(" << key.x2 << "," << key.y2 << "))" << " Pheromone Value: " << key.GetPhero() << " Heuristic Value: " << 1.0/key.GetDistanceBetweenPoints(); 
}

bool PheroKey::operator < (const PheroKey& key) const{
	double dis1 = sqrt((this->x1 * this->x1) + (this->y1 * this->y2)) + sqrt((this->x2 * this->x2) + (this->y2 * this->y2));
	double dis2 = sqrt((key.x1 * key.x1) + (key.y1 * key.y1)) + sqrt((key.x2 * key.x2) + (key.y2 * key.y2));
	if(dis1/2.0 < dis2/2.0){
	return true;
	}else{
	return false;
	}
}

void PheroKey::SetDisBetweenPoint(const double NewDis){
	DisBetweenPoints = NewDis;
}

void PheroKey::ResetDisBetweenPoint(){
	DisBetweenPoints = sqrt( (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

PheroKey::~PheroKey(){
}

