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

unordered_map<PheroKey, double, PheroKeyHash> GraphMap::GetPheroTable() const{
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

double GraphMap::GetPhero(const PheroKey key) const{
	double phero;
	try{
		phero = PheroTable.at(key);
	}catch(out_of_range){
		phero = -1;
	}
	return phero;
}

pair<int,int> GraphMap::GetStartNode(){
	return StartNodePos;
}

pair<int, int> GraphMap::GetEndNode(){
	return EndNodePos;
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
	unordered_map<PheroKey, double, PheroKeyHash>::iterator itr;
	cout << "Key\tElement\n" << endl;
	for(itr = PheroTable.begin(); itr != PheroTable.end(); ++itr){
		cout << itr->first << "\t";
		printf("%f",itr->second);
		cout << endl;
	}
}

void GraphMap::PrintPheroTable(unordered_map<PheroKey, double, PheroKeyHash> p_map){
	unordered_map<PheroKey, double, PheroKeyHash>::iterator itr;
	cout << "Key\tElement\n" << endl;
	for(itr = p_map.begin(); itr != p_map.end(); ++itr){
		cout << itr->first << "\t" << itr->second << endl;
	}
}

void GraphMap::AddNode(const int x1, const int y1, const int x2, const int y2){
	PheroTable[PheroKey(x1, y1, x2, y2)] = DefaultPhero;
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
	PheroTable[key] += value;
}

void GraphMap::UpdatePhero(const PheroKey key, const double value){
	PheroTable[key] += value;
}

void GraphMap::EvapouratePhero(const double e_value){
	unordered_map<PheroKey, double>::iterator itr;
	for(itr = PheroTable.begin(); itr != PheroTable.end(); ++itr){
		itr->second *= e_value;
	}
}


void GraphMap::EvapouratePhero(){
	unordered_map<PheroKey, double>::iterator itr;
	for(itr = PheroTable.begin(); itr != PheroTable.end(); ++itr){
		itr->second *= evap_rate;
	}
}

unordered_map<PheroKey, double, PheroKeyHash> GraphMap::GetAllEdges(const int x1, const int y1){
	unordered_map<PheroKey, double, PheroKeyHash>::iterator itr;
	unordered_map<PheroKey, double, PheroKeyHash> temp_map;
	for(itr = PheroTable.begin(); itr != PheroTable.end(); ++itr){
		if( (itr->first.GetPoint1().first == x1 && itr->first.GetPoint1().second == y1) || (itr->first.GetPoint2().first == x1 && itr->first.GetPoint2().second == y1) ){
			temp_map[itr->first] = itr->second;
		}
	}
	return temp_map;
}

void GraphMap::SetStartNode(const int x, const int y){
	StartNodePos.first = x;
	StartNodePos.second = y;
	state_map[y][x] = "S";
}

void GraphMap::SetEndNode(const int x, const int y){
	EndNodePos.first = x;
	EndNodePos.second = y;
	state_map[y][x] = "F";
}

set<PheroKey> GraphMap::FindBestPathOfIter(){
	set<PheroKey> temp_set;
	set<PheroKey>::reverse_iterator rev_itr;
	rev_itr = temp_set.rbegin();
	int temp_x = StartNodePos.first;
	int temp_y = StartNodePos.second;
	double max_tempphero = -9999999999;
	unordered_map<PheroKey, double, PheroKeyHash>::iterator max_itr;		
	unordered_map<PheroKey, double, PheroKeyHash> temp_edgemap = GetAllEdges(temp_x, temp_y);
	unordered_map<PheroKey, double, PheroKeyHash>::iterator edgemap_itr;	
	for(edgemap_itr=temp_edgemap.begin();edgemap_itr != temp_edgemap.end(); edgemap_itr++){
		if(edgemap_itr->second > max_tempphero){
			max_tempphero = edgemap_itr->second;
			max_itr = edgemap_itr;
		}
	}
	temp_x = max_itr->first.GetPoint2().first;
	temp_y = max_itr->first.GetPoint2().second;
	temp_set.insert(max_itr->first);
	do{
		max_tempphero = -9999999999;
		temp_edgemap = GetAllEdges(temp_x, temp_y);
		for(edgemap_itr=temp_edgemap.begin();edgemap_itr != temp_edgemap.end(); edgemap_itr++){
			if(edgemap_itr->second > max_tempphero && temp_set.find(edgemap_itr->first) == temp_set.end()){
				max_tempphero = edgemap_itr->second;
				max_itr = edgemap_itr;
			}
		}

		temp_x = max_itr->first.GetPoint2().first;
		temp_y = max_itr->first.GetPoint2().second;
		temp_set.insert(max_itr->first);
	
	}while(rev_itr->GetPoint2() != EndNodePos);
	return temp_set;
}
