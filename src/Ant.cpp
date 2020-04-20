#include "Ant.h"

using namespace std;

Ant::Ant(){
	ant_x = 0;
	ant_y = 0;
}

Ant::Ant(const int new_x, const int new_y){
	ant_x = new_x;
	ant_y = new_y;
}


Ant::Ant(const Ant& anthony){
	ant_x = anthony.ant_x;
	ant_y = anthony.ant_y;
	keys_visited = anthony.keys_visited;
}

int Ant::GetX() const{
	return ant_x;
}

int Ant::GetY() const{
	return ant_y;
}

double Ant::GetPheroCount(GraphMap& gmap){
	double pCount = 0;
	vector<shared_ptr<PheroKey>>::iterator kv_itr;
	for(kv_itr = keys_visited.begin(); kv_itr != keys_visited.end(); kv_itr++){
		if(gmap.GetPhero(**kv_itr) != -1){
		pCount += gmap.GetPhero(**kv_itr);
		}else{
		pCount = -1;
		}
	}
	return pCount;
}

double Ant::GetValueOfPath() const{
	double ValueOfPath = 0;
	vector<shared_ptr<PheroKey>>::const_iterator key_itr;
	if(!keys_visited.empty()){
		for(key_itr=keys_visited.begin(); key_itr!=keys_visited.end(); key_itr++){
			ValueOfPath += 1.0/key_itr->get()->GetDistanceBetweenPoints();
		}
		return ValueOfPath;
	}else{
		return ValueOfPath;
	}
}

vector<shared_ptr<PheroKey>> Ant::GetKeysVisited() const{
	return keys_visited;
}

void Ant::SetX(const int new_x){
	ant_x = new_x;
}

void Ant::SetY(const int new_y){
	ant_y = new_y;
}

void Ant::MoveAntToEndNode(GraphMap& gmap, bool first_run){	
	vector<shared_ptr<PheroKey>>::iterator result;
	vector<shared_ptr<PheroKey>> PossibleEdges;
	PossibleEdges = gmap.GetAllEdges(ant_x, ant_y);
	vector<shared_ptr<PheroKey>>::iterator choice;
	for(choice=keys_visited.begin(); choice!=keys_visited.end(); choice++){
		vector<shared_ptr<PheroKey>>::iterator temp_remover;
		for(temp_remover=PossibleEdges.begin(); temp_remover != PossibleEdges.end(); temp_remover++){
			PossibleEdges.erase(temp_remover);
		}
	}
	if(first_run){
		random_device dev;
		mt19937 rng(dev());
		uniform_int_distribution<mt19937::result_type> dist(0, PossibleEdges.size()-1);
		int choice_index = dist(rng);
		result = PossibleEdges.begin();
		advance(result, choice_index);
		keys_visited.push_back(*result);
		ant_x = result->get()->GetX2();
		ant_y = result->get()->GetY2();
	}else{
		double pSet[PossibleEdges.size()];
		double TotalPhero = 0;
		int i = 0;
		for(result=PossibleEdges.begin();result != PossibleEdges.end();result++){
			double phero_temp = gmap.GetPhero(**result) * (1/result->get()->GetDistanceBetweenPoints());
			pSet[i] = phero_temp;
			TotalPhero += phero_temp;
			i += 1;
		}

		double cum = 0;
		long unsigned int ii;
		for(ii=0; ii < sizeof(pSet)/sizeof(*pSet); ii++){
		double current_prob = (pSet[ii]/TotalPhero);
		random_device dev;
		mt19937 rng(dev());
		uniform_real_distribution<double> dist(0.0, 1.0);
		double choice_prob = dist(rng);
		if(choice_prob <= current_prob + cum){
			result = PossibleEdges.begin();
			advance(result, ii);
			keys_visited.push_back(*result);
			ant_x = result->get()->GetX2();
			ant_y = result->get()->GetY2();
			break;
		}
		cum += current_prob;
		}
	}
}

void Ant::MoveAntToStartNode(GraphMap& gmap){
	ant_x = gmap.GetStartX();	
	ant_y = gmap.GetStartY();
}

bool Ant::IsAtNode(const int n_x, const int n_y){
	return (ant_x == n_x && ant_y == n_y);
}

bool Ant::IsOnKey(const PheroKey& key){
	vector<shared_ptr<PheroKey>>::reverse_iterator itr;
	itr = keys_visited.rbegin();
	return (**itr == key);
}

void Ant::PrintVistedKeys() const{
	vector<shared_ptr<PheroKey>>::const_iterator itr;
	for(itr=keys_visited.begin(); itr!=keys_visited.end(); itr++){
		cout << **itr << endl;
	}
}

void Ant::EmptyKV(){
	keys_visited.clear();
}

ostream& operator<<(ostream& out, const Ant& anthony){
	out << "x: " << anthony.GetX() << " y: " << anthony.GetY() << " Node Visitied: " << endl;
	anthony.PrintVistedKeys();
	return out;
}

void Ant::PrintAntInfo(GraphMap& gmap) const{
	cout << "x: " << ant_x << " y: " << ant_y << " Node Visitied: " << endl;
	vector<shared_ptr<PheroKey>>::const_iterator itr;
	for(itr=keys_visited.begin(); itr!=keys_visited.end(); itr++){
		cout << **itr << endl;
	}
}

Ant::~Ant(){
}
