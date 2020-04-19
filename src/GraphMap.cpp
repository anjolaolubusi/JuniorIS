#include "GraphMap.h"

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

GraphMap::GraphMap(const GraphMap& gMap2){
	width = gMap2.width;
	height = gMap2.height;
	state_map = gMap2.state_map;
	evap_rate = gMap2.evap_rate;
	DefaultPhero = gMap2.DefaultPhero;
	PheroTable = gMap2.PheroTable;
	StartX = gMap2.StartX;
	StartY = gMap2.StartY;
	EndX = gMap2.EndX;
	EndY = gMap2.EndY;

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

vector<PheroKey> GraphMap::GetPheroTable() const{
	return PheroTable;
}

double GraphMap::GetPhero(const int x1, const int y1, const int x2, const int y2) const{
	PheroKey key = PheroKey(x1,y1, x2, y2);
	vector<PheroKey>::const_iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(*key_itr == key){
			break;
		}
	}
	return key_itr->GetPhero();
}

double GraphMap::GetPhero(const PheroKey& key) const{
	vector<PheroKey>::const_iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(*key_itr == key){
			break;
		}
	}
	return key_itr->GetPhero();
}

int GraphMap::GetStartX(){
	return StartX;
}

int GraphMap::GetStartY(){
	return StartY;
}

int GraphMap::GetEndX(){
	return EndX;
}

int GraphMap::GetEndY(){
	return EndY;
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
	vector<PheroKey>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		cout << *key_itr << " " << endl;
	}	
}

void GraphMap::PrintPheroTable( vector<PheroKey> p_map){
	vector<PheroKey>::iterator key_itr;
	for(key_itr=p_map.begin(); key_itr != p_map.end(); key_itr++ ){
		cout << *key_itr << " " << endl;
	}	
}

void GraphMap::AddNode(const int x1, const int y1, const int x2, const int y2){
	PheroTable.push_back(PheroKey(x1,y1,x2,y2, MaxPhero));
	if(state_map[y1][x1] != "S" && state_map[y1][x1] != "F"){	
		state_map[y1][x1] = "N";
	}
	if(state_map[y2][x2] != "S" && state_map[y2][x2] != "F"){	
		state_map[y2][x2] = "N";
	}
}

void GraphMap::ChangeState(const int x, const int y, const string new_state){
	state_map[y][x] = new_state;
}

void GraphMap::UpdatePhero(const int x1, const int y1, const int x2, const int y2, const double value){
	PheroKey key = PheroKey(x1, y1, x2, y2);
	vector<PheroKey>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(*key_itr == key){
			break;
		}
	}
	key_itr->UpdatePhero(value);	
}

void GraphMap::UpdatePhero(const PheroKey key, const double value){
	vector<PheroKey>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(*key_itr == key){
			break;
		}
	}
	if(MinPhero <= value && value <= MaxPhero){
		key_itr->UpdatePhero(value);	
	}
}

void GraphMap::EvapouratePhero(const double e_value){
	vector<PheroKey>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		double NewPheroValue = key_itr->GetPhero() * (1 - e_value);
		if(MinPhero <= NewPheroValue){	
			key_itr->UpdatePhero(NewPheroValue);
		}else{
			key_itr->UpdatePhero(MaxPhero);
		}
	}	
}


void GraphMap::EvapouratePhero(){
	vector<PheroKey>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		double NewPheroValue = key_itr->GetPhero() * (1 - evap_rate);
		if(MinPhero <= NewPheroValue){	
			key_itr->UpdatePhero(NewPheroValue);
		}else{
			key_itr->UpdatePhero(MaxPhero);
		}
	}	
}

vector<PheroKey> GraphMap::GetAllEdges(const int x1, const int y1){
	vector<PheroKey> temp_table;
	vector<PheroKey>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		if((key_itr->GetX1() == x1 && key_itr->GetY1() == y1) || (key_itr->GetX2() == x1 && key_itr->GetY2() == y1)){
			temp_table.emplace_back(*key_itr);
		}
	}
	return temp_table;	
}

void GraphMap::SetStartNode(const int x, const int y){
	StartX = x;
	StartY = y;
	state_map[y][x] = "S";
}

void GraphMap::SetEndNode(const int x, const int y){
	EndX = x;
	EndY = y;
	state_map[y][x] = "F";
}

void GraphMap::RemoveEdge(const PheroKey& key){
	vector<PheroKey>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(*key_itr == key){
			break;
		}
	}
	PheroTable.erase(key_itr);
}
