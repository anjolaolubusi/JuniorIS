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
	this->window = new sf::RenderWindow(sf::VideoMode(1152,864), "Ant Colony Optimization Simulator - (MMAS)");
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

			default:
				break;
		}
	}
}

void MMAS::update(){
	this->updateSFMLEvents();
	ImGui::SFML::Update(*window, dtClock.restart());
	HandleGUI();
	StartAlgorithm();
	UpdatePathColours();
}

void MMAS::render(){

	this->window->clear(sf::Color::White);
	vector<sf::Sprite>::iterator node_itr;
	for(node_itr=ListOfNodes.begin(); node_itr != ListOfNodes.end(); node_itr++){
		window->draw(*node_itr);
	}
	vector<PheroEdge>::iterator rect_itr;
	for(rect_itr=ListOfEdges.begin(); rect_itr != ListOfEdges.end(); rect_itr++){
		window->draw(rect_itr->line);
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
	PheroEdge pe;
	pe.x1 = x1;
	pe.x2 = x2;
	pe.y1 = y1;
	pe.y2 = y2;
	pe.line = line;
	ListOfEdges.push_back(pe);
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
	ListOfNodes.push_back(nodeSprite);
	vector<shared_ptr<Ant>>::iterator ant_itr;
	for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
		random_device dev;
		mt19937 rng(dev());
		uniform_real_distribution<double> dist(1.0, 3.0);
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

void MMAS::HandleGUI(){
	ImGui::SetWindowSize("Controls", ImVec2(500,125), ImGuiCond_FirstUseEver);
	ImGui::SetWindowPos("Controls", ImVec2(20,20), ImGuiCond_FirstUseEver);
	ImGui::SetWindowPos("Results", ImVec2(20,165), ImGuiCond_FirstUseEver);
	ImGui::Begin("Controls");
	if(ImGui::Button("Start Simulation")){
		graphMap.StartOver();
		inter_num = 0;
		hasBegun = true;
	}

	if(ImGui::Button("Pause Simulation")){
		hasBegun = false;
	}

	if(ImGui::Button("End Simulation")){
		vector<shared_ptr<Ant>>::iterator ant_itr;
		for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
			ant_itr->get()->MoveAntToStartNode(graphMap);
		}

		for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
			ant_itr->get()->EmptyKV();
		}
		inter_num = 0;
		hasBegun = false;
	}

	if(HasBestPathBeenFound()){
        if(ImGui::Button("Repeat Simulation")){
            hasBegun = true;
        }
	}

	ImGui::SliderFloat("Evaporation Constant", &PheroConst, 0.0f, 1.0f);
	graphMap.SetEvapourationRate(PheroConst);
	ImGui::End();

	ImGui::Begin("Results");
	ImGui::Text("Number of iterations: %d", inter_num);
	ImGui::End();

}

void MMAS::StartAlgorithm(){
	vector<shared_ptr<Ant>>::iterator ant_itr;
	if(!HasBestPathBeenFound() && hasBegun){
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
	}else{
	    for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
			ant_itr->get()->MoveAntToStartNode(graphMap);
		}

		for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
			ant_itr->get()->EmptyKV();
		}
		hasBegun = false;
	}
}

bool MMAS::HasBestPathBeenFound(){
    if(!graphMap.GetBestPathSoFar().empty()){
    vector<shared_ptr<Ant>>::iterator ant_itr = ants.begin();
    for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
        if(ant_itr->get()->GetKeysVisited() != graphMap.GetBestPathSoFar()){
            return false;
            break;
        }
    }
    for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
        if(!ant_itr->get()->GraphAntAtNode()){
            return false;
            break;
        }
    }
    return true;
    }else{
    return false;
    }
}

void MMAS::UpdatePathColours(){
    vector<PheroEdge>::iterator rect_itr;
	for(rect_itr=ListOfEdges.begin(); rect_itr != ListOfEdges.end(); rect_itr++){
        rect_itr->line.setFillColor(sf::Color(0,0,0, 255 * graphMap.GetPhero(rect_itr->x1, rect_itr->y1, rect_itr->x2, rect_itr->y2)/10 ));
	}
}

MMAS::~MMAS(){
delete window;
}

