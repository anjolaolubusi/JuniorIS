#include "Ant.h"

using namespace std;

//Default constructor
Ant::Ant(){
	ant_x = 0;
	ant_y = 0;
	this->shape.setSize(sf::Vector2f(10.f, 10.f));
	this->shape.setFillColor (sf::Color::Blue);
	this->shape.setPosition(0,0);
	this->shape.setOrigin (-12.f, -12.f);
	moveSpeed = 1;
}

// Parameterized constructor
Ant::Ant(const int new_x, const int new_y){
	ant_x = new_x;
	ant_y = new_y;
	this->shape.setSize(sf::Vector2f(10.f, 10.f));
	this->shape.setPosition (ant_x, ant_y);
	this->shape.setFillColor (sf::Color::Blue);
	this->shape.setOrigin (-12.f, -12.f);
}

// Copy Constructor
Ant::Ant(const Ant& anthony){
	ant_x = anthony.ant_x;
	ant_y = anthony.ant_y;
	keys_visited = anthony.keys_visited;
	this->shape = anthony.shape;
	moveSpeed = anthony.moveSpeed;
}

//Returns x position
int Ant::GetX() const{
	return ant_x;
}

//Returns y position
int Ant::GetY() const{
	return ant_y;
}

//Gets pheromone count of path travelled
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

//Gets heuristic value of path
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

//Returns path travelled
vector<shared_ptr<PheroKey>> Ant::GetKeysVisited() const{
	return keys_visited;
}

//Sets the x position
void Ant::SetX(const int new_x){
	ant_x = new_x;
}

//Sets the y position
void Ant::SetY(const int new_y){
	ant_y = new_y;
}

//Moves the ant to end node
void Ant::MoveAntToEndNode(GraphMap& gmap, bool first_run){
	vector<shared_ptr<PheroKey>>::iterator result;
	vector<shared_ptr<PheroKey>> PossibleEdges;
	PossibleEdges = gmap.GetAllEdges(ant_x, ant_y);
	vector<shared_ptr<PheroKey>>::iterator choice;

	if(PossibleEdges.empty()){
		isFin = true;
	}

	for(choice=keys_visited.begin(); choice!=keys_visited.end(); choice++){
		vector<shared_ptr<PheroKey>>::iterator temp_remover;
		for(temp_remover=PossibleEdges.begin(); temp_remover != PossibleEdges.end(); temp_remover++){
			if(PossibleEdges.size() > 0 && !isFin){
				if(**temp_remover == **choice){
				PossibleEdges.erase(temp_remover);
				}
			}else{
				isFin = true;
				break;
			}
		}
	}

    if(PossibleEdges.empty()){
		isFin = true;
	}

	if(!isFin && PossibleEdges.size() > 0){
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
			ant_slope = (ant_y - this->shape.getPosition().y)/((ant_x - this->shape.getPosition().x));
			VecMag = sqrt( ((ant_x - this->shape.getPosition().x) * (ant_x - this->shape.getPosition().x)) + ((ant_y - this->shape.getPosition().y) * (ant_y - this->shape.getPosition().y)) );
			UnitVecX = (ant_x - this->shape.getPosition().x)/VecMag;
			UnitVecY = (ant_y - this->shape.getPosition().y)/VecMag;
			break;
		}
		cum += current_prob;
		}
	}else{
	isFin = true;
	}

}

//Moves the ant to the start node
void Ant::MoveAntToStartNode(GraphMap& gmap){
	ant_x = gmap.GetStartX();
	ant_y = gmap.GetStartY();
	this->shape.setPosition (gmap.GetStartX(), gmap.GetStartY());
	isFin = false;
}

//Check if the ant is at a certain node
bool Ant::IsAtNode(const int n_x, const int n_y){
	return (ant_x == n_x && ant_y == n_y && round(this->shape.getPosition().x) == ant_x && round(this->shape.getPosition().y) == ant_y);
}

//Check if ant is on key
bool Ant::IsOnKey(const PheroKey& key){
	vector<shared_ptr<PheroKey>>::reverse_iterator itr;
	itr = keys_visited.rbegin();
	return (**itr == key);
}

//Prints travelled path
void Ant::PrintVistedKeys() const{
	vector<shared_ptr<PheroKey>>::const_iterator itr;
	for(itr=keys_visited.begin(); itr!=keys_visited.end(); itr++){
		cout << **itr << endl;
	}
}

//Empties the node visited vector
void Ant::EmptyKV(){
	keys_visited.clear();
}

//Output overloader
ostream& operator<<(ostream& out, const Ant& anthony){
	out << "x: " << anthony.GetX() << " y: " << anthony.GetY() << " Node Visitied: " << endl;
	anthony.PrintVistedKeys();
	return out;
}

//Prints the ant object with the proper pheromone count
void Ant::PrintAntInfo(GraphMap& gmap) const{
	cout << "x: " << ant_x << " y: " << ant_y << " Node Visitied: " << endl;
	vector<shared_ptr<PheroKey>>::const_iterator itr;
	for(itr=keys_visited.begin(); itr!=keys_visited.end(); itr++){
		cout << **itr << endl;
	}
}

Ant::~Ant(){
}

//Updates ant's graphical position
void Ant::update(const float& dt){
	if(!this->GraphAntAtNode()){
		if(this->shape.getPosition().x != ant_x){
		this->moveX();
		}
		if(this->shape.getPosition().y != ant_y){
		this->moveY();
		}
	}
}


void Ant::render(sf::RenderTarget* target){
	target->draw(this->shape);
}

void Ant::moveX(){
			VecMag = sqrt( ((ant_x - this->shape.getPosition().x) * (ant_x - this->shape.getPosition().x)) + ((ant_y - this->shape.getPosition().y) * (ant_y - this->shape.getPosition().y)) );
	UnitVecX = (ant_x - this->shape.getPosition().x)/VecMag;
	//UnitVecY = (ant_y - this->shape.getPosition().y)/VecMag;
	this->shape.move(UnitVecX * this->moveSpeed, 0);
}

void Ant::moveY(){
			VecMag = sqrt( ((ant_x - this->shape.getPosition().x) * (ant_x - this->shape.getPosition().x)) + ((ant_y - this->shape.getPosition().y) * (ant_y - this->shape.getPosition().y)) );
			//UnitVecX = (ant_x - this->shape.getPosition().x)/VecMag;
			UnitVecY = (ant_y - this->shape.getPosition().y)/VecMag;
	this->shape.move(0, UnitVecY * this->moveSpeed);
}

bool Ant::GraphAntAtNode(){
	return ((round(this->shape.getPosition().x) == ant_x-1 || round(this->shape.getPosition().x) == ant_x || round(this->shape.getPosition().x) == ant_x+1  ) && (round(this->shape.getPosition().y) == ant_y-1 || round(this->shape.getPosition().y) == ant_y || round(this->shape.getPosition().y) == ant_y+1) );
}

bool Ant::GraphAntAtNode(int x, int y){
	return ((round(this->shape.getPosition().x) == x-1 || round(this->shape.getPosition().x) == x || round(this->shape.getPosition().x) == x+1  ) && (round(this->shape.getPosition().y) == y-1 || round(this->shape.getPosition().y) == y || round(this->shape.getPosition().y) == y+1) );
}

void Ant::SetSpeed(double speed){
	moveSpeed = speed;
}

bool Ant::IsAntFin(){
	return this->isFin;
}

bool Ant::IsPathWalkable(){
    vector<shared_ptr<PheroKey>>::const_iterator itr;
	for(itr=keys_visited.begin(); itr!=keys_visited.end(); itr++){
		if(!itr->get()->GetWalkableState()){
            return false;
            break;
		}
	}
	return true;
}
