#include "MMAS.h"

using namespace std;

MMAS::MMAS(){
	this->initWindow();
	if(!nodeTex.loadFromFile("../res/node.png")){
		cout << "Node Texture Failed To Load" << endl;
	}
	//nodeSprite = new sf::Sprite(nodeTex);
	//nodeSprite->setOrigin ((nodeTex.getSize().x * nodeSprite->getScale().x)/2, (nodeTex.getSize().y * nodeSprite->getScale().y)/2);
	cout << "INIT" << endl;
	view = window->getDefaultView();
	ImGui::SFML::Init(*window);
}

MMAS::MMAS(int startX, int startY, int endX, int endY, int number_of_ants){
	ant_count = number_of_ants;
	graphMap.SetStartNode(startX, startY);
	graphMap.SetEndNode(endX, endY);
	this->initWindow();
	ImGui::SFML::Init(*window);
}

MMAS::MMAS(const MMAS& otherMMAS){
	ant_count = otherMMAS.ant_count;
	ants = otherMMAS.ants;
	graphMap = otherMMAS.graphMap;
}


void MMAS::initWindow(){
	this->window = new sf::RenderWindow(sf::VideoMode(1152,864), "ACO");
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}

void MMAS::updateDt(){
	this->dt = this->dtClock.restart().asSeconds();
}

void MMAS::updateSFMLEvents(){
	while(this->window->pollEvent(this->sfEvent)){
		ImGui::SFML::ProcessEvent(this->sfEvent);
		switch (this->sfEvent.type){
			case sf::Event::Closed:	
				this->window->close();
				break;

			case sf::Event::MouseButtonReleased:
				if(this->sfEvent.mouseButton.button == sf::Mouse::Left){	
					//sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
					//nodeSprite.setPosition ((float)mousePos.x, (float)mousePos.y);
					//ListOfNodes.push_back(nodeSprite);
				}

			case sf::Event::KeyReleased:
				if(this->sfEvent.key.code == sf::Keyboard::P){
					this->PrintPheroTable();
				}
				if(this->sfEvent.key.code == sf::Keyboard::Space){
					this->hasBegun = !this->hasBegun;
				}

			default:
				break;
		}
	}
}

void MMAS::update(){
	this->updateSFMLEvents();
	ImGui::SFML::Update(*window, dtClock.restart());
	//Move ant to the next node or update PheromoenTable
	vector<shared_ptr<Ant>>::iterator ant_itr;
	if(inter_num < 1000 && hasBegun){
		antAtEnd = 0;
	for(ant_itr=ants.begin(); ant_itr!=ants.end(); ant_itr++){
		if(!ant_itr->get()->IsAntFin()){
		if(ant_itr->get()->GraphAntAtNode(graphMap.GetEndX(), graphMap.GetEndY())){
			antAtEnd++;	
		}else{
			if(ant_itr->get()->GraphAntAtNode()){
			//antAtEnd = 0;
			ant_itr->get()->MoveAntToEndNode(graphMap);
			ant_itr->get()->update(dt);
			}else{
			ant_itr->get()->update(dt);
			}
		}
		}else{
		antAtEnd++;
		}
	}
	if(antAtEnd == ant_count){		
		vector<shared_ptr<Ant>>::iterator choice_itr = ants.begin();
		double MaxInfo = -99999.0;
		double test_value = 0;
		for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
			test_value = ant_itr->get()->GetValueOfPath();
			if(MaxInfo < test_value && ant_itr->get()->GetKeysVisited().back()->GetX2() == graphMap.GetEndX() && ant_itr->get()->GetKeysVisited().back()->GetY2() == graphMap.GetEndY()){
				MaxInfo = test_value;
				choice_itr = ant_itr;
			}
		}

		graphMap.SetBestPath(choice_itr->get()->GetKeysVisited());
		graphMap.EvapouratePhero();
		graphMap.UpdatePhero(inter_num);

		for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
			ant_itr->get()->MoveAntToStartNode(graphMap);
		}

		for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
			ant_itr->get()->EmptyKV();
		}
		//this->PrintPheroTable();
		//cout << endl;
		inter_num++;
	}
	}
	ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();
}

void MMAS::render(){

	this->window->clear(sf::Color::White);
	vector<sf::Sprite>::iterator node_itr;
	for(node_itr=ListOfNodes.begin(); node_itr != ListOfNodes.end(); node_itr++){
		window->draw(*node_itr);
	}
	vector<sf::RectangleShape>::iterator rect_itr;
	for(rect_itr=ListOfEdges.begin(); rect_itr != ListOfEdges.end(); rect_itr++){
		window->draw(*rect_itr);
	}
	vector<shared_ptr<Ant>>::iterator ant_itr;
	for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
		ant_itr->get()->render(this->window);
	}	
	ImGui::SFML::Render(*window);
	this->window->display();
}


void MMAS::run(){
	while(this->window->isOpen()){
		this->updateDt();
		this->update();
		this->render();
		this->updateDt();
	}
}

void MMAS::AddNode(const int x, const int y){	
	sf::Sprite nodeSprite(nodeTex);
	nodeSprite.setPosition(x, y);
	cout << "POS CRE" << endl;
	ListOfNodes.push_back(nodeSprite);
}

void MMAS::AddEdge(const int x1, const int y1, const int x2, const int y2){
	//Draw Line
	float deltaX = x2-x1;
	float deltaY = y2-y1;
	float ang = atan(deltaY/deltaX) * (180/M_PI);
	sf::RectangleShape line(sf::Vector2f(sqrt((deltaX * deltaX) + (deltaY * deltaY)) , 5.f));
	line.setFillColor (sf::Color::Black);
	line.rotate (ang);
	line.setPosition (x1+16, y1+16);
	ListOfEdges.push_back(line);
	graphMap.AddEdge(x1, y1, x2, y2);
}

void MMAS::AddEdge(const PheroKey& key){
	graphMap.AddEdge(key);
}

void MMAS::RemoveEdge(const PheroKey& key){
	graphMap.RemoveEdge(key);
}

void MMAS::SetStartNode(const int x, const int y){
	graphMap.SetStartNode(x, y);
	for(int i = 0; i < ant_count; i++){	
		ants.push_back(make_shared<Ant>(graphMap.GetStartX(), graphMap.GetStartY()));
	}
	sf::Sprite nodeSprite(nodeTex);
	nodeSprite.setPosition(x, y);
	cout << "START POS CRE" << endl;
	ListOfNodes.push_back(nodeSprite);
	vector<shared_ptr<Ant>>::iterator ant_itr;
	for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
		random_device dev;
		mt19937 rng(dev());
		uniform_real_distribution<double> dist(1.0, 3.5);
		float ant_speed = dist(rng);
		ant_itr->get()->SetSpeed(ant_speed);
	}	
	
	StartHasBeenSet = true;
}

void MMAS::SetEndNode(const int x, const int y){
	graphMap.SetEndNode(x, y);
	sf::Sprite nodeSprite(nodeTex);
	nodeSprite.setPosition(x, y);
	ListOfNodes.push_back(nodeSprite);
	cout << "END POS CRE" << endl;
	EndHasBeenSet = true;
}

void MMAS::SetNumberOfAnts(const int number_of_ants){
	int diff = number_of_ants - ant_count;
	if(diff > 0){
		for(int i=0; i < diff; i++){
			ants.push_back(make_shared<Ant>(graphMap.GetStartX(), graphMap.GetStartY()));
		}
	}else if(diff < 0){
		diff = 0 - diff;
		for(int i = 0; i < diff; i++){
			ants.pop_back();
		}
	}
}

void MMAS::PrintPheroTable(){
	graphMap.PrintPheroTable();
}


void MMAS::StartAlgorithm(){

}

MMAS::~MMAS(){
delete window;
}

