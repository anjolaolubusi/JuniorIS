#include "MMAS.h"

using namespace std;

MMAS::MMAS(){
}

MMAS::MMAS(int startX, int startY, int endX, int endY, int number_of_ants){
	ant_count = number_of_ants;
	graphMap.SetStartNode(startX, startY);
	graphMap.SetEndNode(endX, endY);
}

MMAS::MMAS(const MMAS& otherMMAS){
	ant_count = otherMMAS.ant_count;
	ants = otherMMAS.ants;
	graphMap = otherMMAS.graphMap;
}

void MMAS::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
	int flags = 0;
	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		cout << "SDL is initialized" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(window){
			cout << "Window created" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created" << endl;
		}
		isRunning = true;
	}else{
		isRunning = false;
	}
}

void MMAS::handleEvents(){
	SDL_Event event;
	SDL_PollEvent (&event);
	switch (event.type){
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void MMAS::update(){

}

void MMAS::render(){
	SDL_RenderClear(renderer);
	//Add stuff to Render
	SDL_RenderPresent(renderer);
}

void MMAS::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned" << endl;
}

void MMAS::AddEdge(const int x1, const int y1, const int x2, const int y2){
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
		ants.push_back(Ant(graphMap.GetStartX(), graphMap.GetStartY()));
	}
	StartHasBeenSet = true;
}

void MMAS::SetEndNode(const int x, const int y){
	graphMap.SetEndNode(x, y);
	EndHasBeenSet = true;
}

void MMAS::SetNumberOfAnts(const int number_of_ants){
	int diff = number_of_ants - ant_count;
	if(diff > 0){
		for(int i=0; i < diff; i++){
			ants.push_back(Ant(graphMap.GetStartX(), graphMap.GetStartY()));
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

void MMAS::PrintStateGrid(){
	graphMap.PrintStateGrid();
}

void MMAS::StartAlgorithm(){

for(int inter = 0; inter < 50; inter++){

	vector<Ant>::iterator ant_itr;

for (ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
	ant_itr->MoveAntToEndNode(graphMap, true);
	while(ant_itr->GetX() != graphMap.GetEndX() && ant_itr->GetY() != graphMap.GetEndY()){
	ant_itr->MoveAntToEndNode(graphMap);
	}

}

//Add logic to get best path of iteration

vector<Ant>::iterator choice_itr = ants.begin();
double MaxInfo = -99999.0;
double test_value = 0;
for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
	test_value = ant_itr->GetValueOfPath();
	if(MaxInfo < test_value){
		MaxInfo = test_value;
		choice_itr = ant_itr;
	}
}

graphMap.SetBestPath(choice_itr->GetKeysVisited());
graphMap.EvapouratePhero();
graphMap.UpdatePhero(inter);


for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
	ant_itr->MoveAntToStartNode(graphMap);
}


for(ant_itr=ants.begin(); ant_itr != ants.end(); ant_itr++){
	ant_itr->EmptyKV();
}

}

cout << "FINAL"  << endl;
graphMap.PrintPheroTable();
}

MMAS::~MMAS(){
}

