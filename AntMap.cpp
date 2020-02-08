#include <iostream>
#include <string.h>
#include "AntMap.h"

AntMap::AntMap(){
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


AntMap::AntMap(int n_width, int n_height){
width = n_width;
height = n_height;
phero_map = new int*[width];
state_map = new string*[height];

for (int i = 0; i < width; i++){
	phero_map[i] = new int[height];
	state_map[i] = new string[height];	
	
}
}

AntMap::~AntMap(){
for (int i = 0; i < width; i++){
		delete [] phero_map[i];
		delete [] state_map[i];
}
delete [] phero_map;
delete [] state_map;
}

string** AntMap::GetStateArray(){
return state_map;
}

string AntMap::GetState(int x, int y){
return state_map[x][y];
}

int** AntMap::GetPheroArray(){
return phero_map;
}

int AntMap::GetPhero(int x, int y){
return phero_map[x][y];
}

void AntMap::PrintPheroGrid(){
	for( int i=0;i < width;i++){
		for(int j=0;j < height;j++){
			cout << phero_map[i][j] << " ";
		}
		cout << endl;
	}
}

void AntMap::PrintStateGrid(){
	for( int i=0;i < width;i++){
		for(int j=0;j < height;j++){
			cout << state_map[i][j] << " ";
		}
		cout << endl;
	}

}
