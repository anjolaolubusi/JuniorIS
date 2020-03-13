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

void Ant::MoveAntToEndNode(GraphMap& gmap, bool first_run){	
	map<PheroKey, double>::iterator result;
	map<PheroKey, double> map2;
	map2 = gmap.GetAllEdges(x, y);
	set<PheroKey>::iterator choice;
	for(choice=nodes_visited.begin(); choice!=nodes_visited.end(); choice++){
		map2.erase(*choice);
	}
	if(first_run){
		random_device dev;
		mt19937 rng(dev());
		uniform_int_distribution<mt19937::result_type> dist(0, map2.size()-1);
		int choice_index = dist(rng);
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
		random_device dev;
		mt19937 rng(dev());
		uniform_real_distribution<double> dist(0.0, 1.0);
		double choice_prob = dist(rng);
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

void Ant::MoveAntToStartNode(GraphMap& gmap){
	set<PheroKey>::reverse_iterator itr;
	for(itr=nodes_visited.rbegin(); itr!=nodes_visited.rend(); itr++){
		gmap.UpdatePhero(*itr, 5/(itr->GetDistanceBetweenPoints()));
		x = itr->GetPoint1().first;
		y = itr->GetPoint1().second;
	}
}

bool Ant::IsAtNode(const int n_x, const int n_y){
	return (x == n_x && y == n_y);
}

bool Ant::IsOnKey(const PheroKey& key){
	set<PheroKey>::reverse_iterator itr;
	itr = nodes_visited.rbegin();
	return (itr->GetPoint1() == key.GetPoint1() && itr->GetPoint2() == key.GetPoint2());
}

void Ant::PrintVistedNodes(){
	set<PheroKey>::iterator itr;
	for(itr=nodes_visited.begin(); itr!=nodes_visited.end(); itr++){
		cout << *itr << endl;
	}
}

void Ant::EmptyNV(){
	nodes_visited.clear();
}

ostream& operator<<(ostream& out, const Ant anthony){
	out << "x: " << anthony.x << " y: " << anthony.y << " Node Visitied: ";
	set<PheroKey>::iterator itr;
	for(itr=anthony.nodes_visited.begin(); itr!=anthony.nodes_visited.end(); itr++){
		out << *itr << " ";
	}
	return out;
}
