#include "Ant.h"

using namespace std;

Ant::Ant(){
	x = 0;
	y = 0;
}

Ant::Ant(const int new_x, const int new_y){
	x = new_x;
	y = new_y;
}

Ant::Ant(pair<int, int> p1){
	x = p1.first;
	y = p1.second;
}

Ant::Ant(const Ant& anthony){
	x = anthony.x;
	y = anthony.y;
	nodes_visited = anthony.nodes_visited;
}

int Ant::GetX() const{
	return x;
}

int Ant::GetY() const{
	return y;
}

set<PheroKey> Ant::GetNodesVisited(){
	return nodes_visited;
}

void Ant::SetX(const int new_x){
	x = new_x;
}

void Ant::SetY(const int new_y){
	y = new_y;
}

void Ant::MoveAnt(GraphMap& gmap, bool first_run){	
	map<PheroKey, double>::iterator result;
	map<PheroKey, double> map2;
	map2 = gmap.GetAllEdges(x, y);
	set<PheroKey>::iterator choice;
	for(choice=nodes_visited.begin(); choice!=nodes_visited.end(); choice++){
		map2.erase(*choice);
	}
	if(first_run){
		srand(time(0));
		int choice_index = rand() % (map2.size());
		result = map2.begin();
		advance(result, choice_index);
		nodes_visited.insert(PheroKey(x, y, result->first.GetPoint2().first, result->first.GetPoint2().second));
		x = result->first.GetPoint2().first;
		y = result->first.GetPoint2().second;
	}else{
		double pSet[map2.size()];
		double TotalPhero = 0;
		int i = 0;
		for(result=map2.begin();result != map2.end();result++){
			double phero_temp = gmap.GetPheroTable()[result->first] * (1/result->first.GetDistanceBetweenPoints());
			pSet[i] = phero_temp;
			TotalPhero += phero_temp;
			i += 1;
		}

		double cum = 0;
		long unsigned int ii;
		for(ii=0; ii < sizeof(pSet)/sizeof(*pSet); ii++){
		double current_prob = (pSet[ii]/TotalPhero);
		srand(time(0));
		double choice_prob = (double)rand() / (double)RAND_MAX;
		if(choice_prob <= current_prob + cum){
			result = map2.begin();
			advance(result, ii);
			nodes_visited.insert(PheroKey(x, y, result->first.GetPoint2().first, result->first.GetPoint2().second));
			x = result->first.GetPoint2().first;
			y = result->first.GetPoint2().second;
			break;			
		}
		cum += current_prob;
		}
	}
}

void Ant::PrintVistedNodes(){
	set<PheroKey>::iterator itr;
	for(itr=nodes_visited.begin(); itr!=nodes_visited.end(); itr++){
		cout << *itr << endl;
	}
}

ostream& operator<<(ostream& out, const Ant anthony){
	out << "x: " << anthony.x << " y: " << anthony.y << " Node Visitied: ";
	set<PheroKey>::iterator itr;
	for(itr=anthony.nodes_visited.begin(); itr!=anthony.nodes_visited.end(); itr++){
		out << *itr << " ";
	}
	return out;
}
