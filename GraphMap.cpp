#include <iostream>
#include <string.h>
#include "GraphMap.h"

GraphMap::GraphMap(){
width = 20;
height = 20;
phero_map = new int*[width];
state_map = new string*[height];

for (int i = 0; i < width; i++){
	phero_map[i] = new int[height];
	state_map[i] = new string[height];	
	
}

for(int i = 0; i < width; i++){
	for(int j=0;j < height; j++){
		state_map[i][j] = "*";
	}
}

}


GraphMap::GraphMap(int n_width, int n_height){
width = n_width;
height = n_height;
phero_map = new int*[width];
state_map = new string*[height];

for (int i = 0; i < width; i++){
	phero_map[i] = new int[height];
	state_map[i] = new string[height];	
	
}
}

GraphMap::~GraphMap(){
for (int i = 0; i < width; i++){
		delete [] phero_map[i];
		delete [] state_map[i];
}
delete [] phero_map;
delete [] state_map;
}

string** GraphMap::GetStateArray(){
return state_map;
}

string GraphMap::GetState(int x, int y){
return state_map[x][y];
}

int** GraphMap::GetPheroArray(){
return phero_map;
}

int GraphMap::GetPhero(int x, int y){
return phero_map[x][y];
}

void GraphMap::PrintPheroGrid(){
	for( int i=0;i < width;i++){
		for(int j=0;j < height;j++){
			cout << phero_map[i][j] << " ";
		}
		cout << endl;
	}
}

void GraphMap::PrintStateGrid(){
	for( int i=0;i < width;i++){
		for(int j=0;j < height;j++){
			cout << state_map[i][j] << " ";
		}
		cout << endl;
	}

}
