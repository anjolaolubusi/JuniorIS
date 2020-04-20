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

vector<shared_ptr<PheroKey>> GraphMap::GetPheroTable() const{
	return PheroTable;
}


double GraphMap::GetPhero(const int x1, const int y1, const int x2, const int y2) const{
	PheroKey key = PheroKey(x1,y1, x2, y2, MaxPhero);
	vector<shared_ptr<PheroKey>>::const_iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(**key_itr == key){
			break;
		}
	}
	return key_itr->get()->GetPhero();
}

double GraphMap::GetPhero(const PheroKey& key) const{
	vector<shared_ptr<PheroKey>>::const_iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(**key_itr == key){
			break;
		}
	}
	return key_itr->get()->GetPhero();
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

vector<shared_ptr<PheroKey>> GraphMap::GetBestPathOfIter() {
	return BestPathOfIter;
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
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		cout << **key_itr << " " << endl;
	}	
}

void GraphMap::PrintPheroTable( vector<shared_ptr<PheroKey>> p_map){
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=p_map.begin(); key_itr != p_map.end(); key_itr++ ){
		cout << **key_itr << " " << endl;
	}	
}

void GraphMap::AddNode(const int x1, const int y1, const int x2, const int y2){
	PheroTable.push_back(make_shared<PheroKey>(x1,y1,x2,y2, MaxPhero));
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



void GraphMap::UpdatePhero(int inter_num){
	if(!BestPathSoFar.empty() && !BestPathOfIter.empty()){
		if(inter_num % 5 == 0){
			vector<shared_ptr<PheroKey>>::iterator key_itr;
			double dis = 0;
			double newVal = 0;
			for(key_itr=BestPathSoFar.begin(); key_itr != BestPathSoFar.end(); key_itr++){
				dis += 1.0/key_itr->get()->GetDistanceBetweenPoints();
				newVal = key_itr->get()->GetPhero() + (1/key_itr->get()->GetDistanceBetweenPoints());
				key_itr->get()->UpdatePhero(newVal);
			}
			MaxPhero = dis/evap_rate;
		}else{
			vector<shared_ptr<PheroKey>>::iterator key_itr;
			double dis = 0;
			double newVal = 0;
			for(key_itr=BestPathOfIter.begin(); key_itr != BestPathOfIter.end(); key_itr++){
				dis += 1.0/key_itr->get()->GetDistanceBetweenPoints();
				newVal = key_itr->get()->GetPhero() + (1/key_itr->get()->GetDistanceBetweenPoints());
				key_itr->get()->UpdatePhero(newVal);
			}
			MaxPhero = dis/evap_rate;
		}
	}
}

void GraphMap::EvapouratePhero(const double e_value){
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		double NewPheroValue = key_itr->get()->GetPhero() * (1 - e_value);
		if(MinPhero <= NewPheroValue){	
			key_itr->get()->ReplacePhero(NewPheroValue);
		}
	}	
}


void GraphMap::EvapouratePhero(){
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		double NewPheroValue = key_itr->get()->GetPhero() * (1 - evap_rate);
		if(MinPhero <= NewPheroValue){	
			key_itr->get()->ReplacePhero(NewPheroValue);
		}
	}	
}

vector<shared_ptr<PheroKey>> GraphMap::GetAllEdges(const int x1, const int y1){
	vector<shared_ptr<PheroKey>> temp_table;
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		if((key_itr->get()->GetX1() == x1 && key_itr->get()->GetY1() == y1) || (key_itr->get()->GetX2() == x1 && key_itr->get()->GetY2() == y1)){
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
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
		if(**key_itr == key){
			break;
		}
	}
	PheroTable.erase(key_itr);
}

//pre-conditon: key is the best path of the iteration
void GraphMap::SetBestPath(vector<shared_ptr<PheroKey>> BestPath){
	BestPathOfIter = BestPath;
	double InvOfIter = 0;
	double InvOfBest = 0;
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=BestPathOfIter.begin(); key_itr != BestPathOfIter.end(); key_itr++){
		InvOfIter += 1.0/key_itr->get()->GetDistanceBetweenPoints();
	}
	
	if(!BestPathSoFar.empty()){
		for(key_itr=BestPathSoFar.begin(); key_itr != BestPathSoFar.end(); key_itr++){
			InvOfBest += 1.0/key_itr->get()->GetDistanceBetweenPoints();
		}
		if(InvOfIter > InvOfBest){
			BestPathSoFar = BestPathOfIter;
		}
	}else{
		BestPathSoFar = BestPath;
	}
}

