#include "GraphMap.h"

using namespace std;


GraphMap::GraphMap(){
	width = 20;
	height = 20;
}


GraphMap::GraphMap(int n_width, int n_height){
	width = n_width;
 	height = n_height;
}

GraphMap::GraphMap(const GraphMap& gMap2){
	width = gMap2.width;
	height = gMap2.height;
	evap_rate = gMap2.evap_rate;
	DefaultPhero = gMap2.DefaultPhero;
	PheroTable = gMap2.PheroTable;
	StartX = gMap2.StartX;
	StartY = gMap2.StartY;
	EndX = gMap2.EndX;
	EndY = gMap2.EndY;

}

GraphMap::~GraphMap(){
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

double GraphMap::GetMaxOfPheroTable() const{
    double MAXPhero = -9999;
    vector<shared_ptr<PheroKey>>::const_iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++){
            if(MAXPhero < key_itr->get()->GetPhero()){
                MAXPhero = key_itr->get()->GetPhero();
            }
	}
	return MaxPhero;
}

double GraphMap::GetMaxPhero() const{
    return MaxPhero;
}

vector<shared_ptr<PheroKey>> GraphMap::GetBestPathOfIter() {
	return BestPathOfIter;
}

vector<shared_ptr<PheroKey>> GraphMap::GetBestPathSoFar(){
	return BestPathSoFar;
}


void GraphMap::PrintPheroTable(){
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		cout << **key_itr << " " << endl;
	}
	cout << "Best Path So Far: " << endl;
	for(key_itr=BestPathSoFar.begin(); key_itr != BestPathSoFar.end(); key_itr++){
		cout << **key_itr << " " << endl;
	}
}

void GraphMap::PrintPheroTable( vector<shared_ptr<PheroKey>> p_map){
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=p_map.begin(); key_itr != p_map.end(); key_itr++ ){
		cout << **key_itr << " " << endl;
	}
}


void GraphMap::AddEdge(const int x1, const int y1, const int x2, const int y2){
	PheroTable.push_back(make_shared<PheroKey>(x1,y1,x2,y2, MaxPhero));
}

void GraphMap::AddEdge(const PheroKey& key){
	PheroTable.push_back(make_shared<PheroKey>(key.GetX1(),key.GetX2(),key.GetY1(),key.GetY2(), key.GetPhero()));
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
		if(key_itr->get()->GetWalkableState()){
            double NewPheroValue = key_itr->get()->GetPhero() * (1 - evap_rate);
            if(MinPhero <= NewPheroValue){
                key_itr->get()->ReplacePhero(NewPheroValue);
            }else{
                key_itr->get()->ReplacePhero(MinPhero);
            }
		}
	}
}

vector<shared_ptr<PheroKey>> GraphMap::GetAllEdges(const int x1, const int y1){
	vector<shared_ptr<PheroKey>> temp_table;
	vector<shared_ptr<PheroKey>>::iterator key_itr;
	for(key_itr=PheroTable.begin(); key_itr != PheroTable.end(); key_itr++ ){
		if( key_itr->get()->GetWalkableState() && ((key_itr->get()->GetX1() == x1 && key_itr->get()->GetY1() == y1) || (key_itr->get()->GetX2() == x1 && key_itr->get()->GetY2() == y1)) ){
			temp_table.emplace_back(*key_itr);
		}
	}
	return temp_table;
}


void GraphMap::SetStartNode(const int x, const int y){
	StartX = x;
	StartY = y;
}

void GraphMap::SetEndNode(const int x, const int y){
	EndX = x;
	EndY = y;
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

void GraphMap::SetEvapourationRate(double NewRate){
	evap_rate = NewRate;
}

void GraphMap::StartOver(){
    BestPathOfIter.clear();
    BestPathOfIter.clear();
    vector<shared_ptr<PheroKey>>::iterator key_itr;
    for(key_itr=PheroTable.begin();key_itr != PheroTable.end(); key_itr++){
        key_itr->get()->ReplacePhero(DefaultPhero);
        key_itr->get()->SetWalkableState(true);
    }
    MaxPhero = DefaultPhero;
}

void GraphMap::SetSnowProb(double newProb){
    SnowProb = newProb;
}

double GraphMap::GetSnowProb() const{
    return SnowProb;
}

void GraphMap::CanadianSnow(){
    vector<shared_ptr<PheroKey>>::iterator key_itr;
    for(key_itr=PheroTable.begin();key_itr != PheroTable.end(); key_itr++){
        random_device dev;
		mt19937 rng(dev());
		uniform_real_distribution<double> dist(0.0, 1.0);
		double choice_prob = dist(rng);
		if(choice_prob <= SnowProb){
            key_itr->get()->SetWalkableState(false);
		}else{
            key_itr->get()->SetWalkableState(true);
		}
    }
}

bool GraphMap::GetWalkable(int x1, int y1, int x2, int y2) const{
    PheroKey key = PheroKey(x1, y1, x2, y2, 0);
    vector<shared_ptr<PheroKey>>::const_iterator key_itr;
    for(key_itr=PheroTable.begin();key_itr != PheroTable.end(); key_itr++){
        if(**key_itr == key){
            return key_itr->get()->GetWalkableState();
            break;
        }
    }
    return false;
}

void GraphMap::MakeGraphWalkable(){
    vector<shared_ptr<PheroKey>>::const_iterator key_itr;
    for(key_itr=PheroTable.begin();key_itr != PheroTable.end(); key_itr++){
            key_itr->get()->SetWalkableState(true);
    }
}

void GraphMap::ClearBestPath(){
    BestPathSoFar.clear();
}

void GraphMap::ResetPheromoneTable(){
    vector<shared_ptr<PheroKey>>::const_iterator key_itr;
    for(key_itr=PheroTable.begin();key_itr != PheroTable.end(); key_itr++){
            key_itr->get()->ReplacePhero(MaxPhero);
    }
}
