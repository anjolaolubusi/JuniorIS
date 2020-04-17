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
	nodes_visited = anthony.nodes_visited;
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
	for(nv_itr = nodes_visited.begin(); nv_itr != nodes_visited.end(); nv_itr++){
		if(gmap.GetPhero(*nv_itr) != -1){
		pCount += gmap.GetPhero(*nv_itr);
		}else{
		pCount = -1;
		}
	}
	return pCount;
}

vector<PheroKey> Ant::GetNodesVisited() const{
	return nodes_visited;
}

void Ant::SetX(const int new_x){
	ant_x = new_x;
}

void Ant::SetY(const int new_y){
	ant_y = new_y;
}

void Ant::MoveAntToEndNode(GraphMap& gmap, bool first_run){	
	vector<PheroKey>::iterator result;
	vector<PheroKey> map2;
	map2 = gmap.GetAllEdges(ant_x, ant_y);
	vector<PheroKey>::iterator choice;
	for(choice=nodes_visited.begin(); choice!=nodes_visited.end(); choice++){
		vector<PheroKey>::iterator temp_remover = find(map2.begin(), map2.end(), *choice);
		map2.erase(temp_remover);
	}
	if(first_run){
		random_device dev;
		mt19937 rng(dev());
		uniform_int_distribution<mt19937::result_type> dist(0, map2.size()-1);
		int choice_index = dist(rng);
		result = map2.begin();
		advance(result, choice_index);
		nodes_visited.push_back(PheroKey(ant_x, ant_y, result->x2, result->y2));
		ant_x = result->x2;
		ant_y = result->y2;
	}else{
		double pSet[map2.size()];
		double TotalPhero = 0;
		int i = 0;
		for(result=map2.begin();result != map2.end();result++){
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
			result = map2.begin();
			advance(result, ii);
			nodes_visited.push_back(PheroKey(ant_x, ant_y, result->x2, result->y2));
			ant_x = result->x2;
			ant_y = result->y2;
			break;
		}
		cum += current_prob;
		}
	}
}

void Ant::MoveAntToStartNode(GraphMap& gmap){
	vector<PheroKey>::reverse_iterator itr;
	for(itr=nodes_visited.rbegin(); itr!=nodes_visited.rend(); itr++){
		gmap.UpdatePhero(*itr, 5/(itr->GetDistanceBetweenPoints()));
		ant_x = itr->x1;
		ant_y = itr->y1;
	}
}

bool Ant::IsAtNode(const int n_x, const int n_y){
	return (ant_x == n_x && ant_y == n_y);
}

bool Ant::IsOnKey(const PheroKey& key){
	vector<PheroKey>::reverse_iterator itr;
	itr = nodes_visited.rbegin();
	return (itr->x1 == key.x1 && itr->x2 == key.x2);
}

void Ant::PrintVistedNodes() const{
	vector<PheroKey>::const_iterator itr;
	for(itr=nodes_visited.begin(); itr!=nodes_visited.end(); itr++){
		cout << *itr << endl;
	}
}

void Ant::EmptyNV(){
	nodes_visited.clear();
}

ostream& operator<<(ostream& out, const Ant& anthony){
	out << "x: " << anthony.GetX() << " y: " << anthony.GetY() << " Node Visitied: " << endl;
	anthony.PrintVistedNodes();
	return out;
}

void Ant::PrintAntInfo(GraphMap& gmap) const{
	cout << "x: " << ant_x << " y: " << ant_y << " Node Visitied: " << endl;
	vector<PheroKey>::const_iterator itr;
	for(itr=nodes_visited.begin(); itr!=nodes_visited.end(); itr++){
		cout << "((" << itr->x1 << "," << itr->y1 << "),(" << itr->x2 << "," << itr->y2 << ") Pheronmone Value: " << gmap.GetPhero(*itr) << endl;
	}
}

Ant::~Ant(){
}
