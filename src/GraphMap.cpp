#include <iostream>
#include "GraphMap.h"
#include <map>
#include "PheroKey.h"

using namespace std;

GraphMap::GraphMap(){
	width = 20;
	height = 20;
	state_map = new string*[height];
	for (int i = 0; i < height; i++){
		state_map[i] = new string[width];	
	}
	for(int i = 0; i < height; i++){
		for(int j=0;j < width; j++){
			state_map[i][j] = "*";
		}
	}	
}


GraphMap::GraphMap(int n_width, int n_height){
	width = n_width;
 	height = n_height;
	state_map = new string*[height];
	for (int i = 0; i < width; i++){
		state_map[i] = new string[height];	
	}
}

GraphMap::~GraphMap(){
	 for (int i = 0; i < width; i++){
		delete [] state_map[i];
	}
	delete [] state_map;
}

string** GraphMap::GetStateArray() const{
	return state_map;
}

string GraphMap::GetState(int x, int y) const{
	return state_map[x][y];
}

map<PheroKey, double> GraphMap::GetPheroTable() const{
	return PheroTable;
}

double GraphMap::GetPhero(const int x1, const int y1, const int x2, const int y2) const{
	PheroKey key = PheroKey(pair<int, int>(x1, y1), pair<int, int>(x2, y2));
	double phero;
	try{
		phero = PheroTable.at(key);
	}catch(out_of_range){
		phero = -1;
	}
	return phero;
}

void GraphMap::PrintStateGrid(){
	for( int i=0;i < height;i++){
		for(int j=0;j < width;j++){
			cout << state_map[i][j] << " ";
		}
		cout << endl;
	}
}

void GraphMap::PrintPheroTable(){
	map<PheroKey, double>::iterator itr;
	cout << "Key\tElement\n" << endl;
	for(itr = PheroTable.begin(); itr != PheroTable.end(); ++itr){
		cout << itr->first << "\t" << itr->second << endl;
	}
}

void GraphMap::ChangeState(const int x, const int y, const string new_state){
	state_map[y][x] = new_state;
}

void GraphMap::UpdatePhero(const int x1, const int y1, const int x2, const int y2, const double value){
	PheroKey key = PheroKey(x1, y1, x2, y2);
	PheroTable[key] += value;
} 
