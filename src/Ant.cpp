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
	vector<PheroKey>::iterator nv_itr;
	for(nv_itr = keys_visited.begin(); nv_itr != keys_visited.end(); nv_itr++){
		if(gmap.GetPhero(*nv_itr) != -1){
		pCount += gmap.GetPhero(*nv_itr);
		}else{
		pCount = -1;
		}
	}
	return pCount;
}

vector<PheroKey> Ant::GetKeysVisited() const{
	return keys_visited;
}

void Ant::SetX(const int new_x){
	ant_x = new_x;
}

void Ant::SetY(const int new_y){
	ant_y = new_y;
}

void Ant::MoveAntToEndNode(GraphMap& gmap, bool first_run){	
	vector<PheroKey>::iterator result;
	vector<PheroKey> PossibleEdges;
	PossibleEdges = gmap.GetAllEdges(ant_x, ant_y);
	vector<PheroKey>::iterator choice;
	for(choice=keys_visited.begin(); choice!=keys_visited.end(); choice++){
		vector<PheroKey>::iterator temp_remover;
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
		keys_visited.push_back(PheroKey(ant_x, ant_y, result->GetX2(), result->GetY2()));
		ant_x = result->GetX2();
		ant_y = result->GetY2();
	}else{
		double pSet[PossibleEdges.size()];
		double TotalPhero = 0;
		int i = 0;
		for(result=PossibleEdges.begin();result != PossibleEdges.end();result++){
			double phero_temp = gmap.GetPhero(*result) * (1/result->GetDistanceBetweenPoints());
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
			keys_visited.push_back(PheroKey(ant_x, ant_y, result->GetX2(), result->GetY2()));
			ant_x = result->GetX2();
			ant_y = result->GetY2();
			break;
		}
		cum += current_prob;
		}
	}
}

void Ant::MoveAntToStartNode(GraphMap& gmap){
	vector<PheroKey>::reverse_iterator itr;
	for(itr=keys_visited.rbegin(); itr!=keys_visited.rend(); itr++){
		gmap.UpdatePhero(*itr, 5/(itr->GetDistanceBetweenPoints()));
	}
	ant_x = gmap.GetStartX();	
	ant_y = gmap.GetStartY();
}

bool Ant::IsAtNode(const int n_x, const int n_y){
	return (ant_x == n_x && ant_y == n_y);
}

bool Ant::IsOnKey(const PheroKey& key){
	vector<PheroKey>::reverse_iterator itr;
	itr = keys_visited.rbegin();
	return (*itr == key);
}

void Ant::PrintVistedKeys() const{
	vector<PheroKey>::const_iterator itr;
	for(itr=keys_visited.begin(); itr!=keys_visited.end(); itr++){
		cout << *itr << endl;
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
	vector<PheroKey>::const_iterator itr;
	for(itr=keys_visited.begin(); itr!=keys_visited.end(); itr++){
		cout << "((" << itr->GetX1() << "," << itr->GetY1() << "),(" << itr->GetX2() << "," << itr->GetY2() << ") Pheronmone Value: " << gmap.GetPhero(*itr) << endl;
	}
}

Ant::~Ant(){
}
