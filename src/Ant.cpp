#include "Ant.h"

using namespace std;

Ant::Ant(){
	x = 0;
	y = 0;
}

Ant::Ant(const int new_x, const int new_y){
	x = new_x;
	y = new_y;
}

int Ant::GetX() const{
	return x;
}

int Ant::GetY() const{
	return y;
}

void Ant::SetX(const int new_x){
	x = new_x;
}

void Ant::SetY(const int new_y){
	y = new_y;
}

void Ant::MoveAnt(set<PheroKey> SAPE, map<PheroKey, double> pheroMap){	
	vector<double> pSet;
	double TotalPhero = 0;
	set<PheroKey>::iterator itr;
	for(itr=SAPE.begin(); itr != SAPE.end(); ++itr){
		if(nodes_visited.find(*itr) != nodes_visited.end()){
			SAPE.erase(itr);
		}
	}

	for(itr= SAPE.begin(); itr != SAPE.end(); ++itr){
		TotalPhero += pheroMap[*itr] * itr->GetDistanceBetweenPoints();
	}

	itr=SAPE.begin();
	for(int i = 0; i < SAPE.size(); i++){
		pSet.push_back((pheroMap[*itr] * (1/(itr->GetDistanceBetweenPoints())))/(TotalPhero));
		itr++;
	}

	double maxIndex = std::max_element(pSet.begin(),pSet.end()) - pSet.begin();
	itr = SAPE.begin();

	advance(itr, maxIndex);
	nodes_visited.insert(*itr);
	x = itr->GetPoint2().first;
	y = itr->GetPoint2().second;
}
