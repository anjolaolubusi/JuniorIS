#include "MMAS.h"
using namespace std;


//TODO: Added Error Checks
MMAS* am = nullptr;

int main(int argc, const char * argv[])
{

	am = new MMAS();

	am->init("ACO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while(am->running()){
		am->handleEvents();
		am->update();
		am->render();
	}

	am->clean();

am->SetStartNode(5,5);
am->SetEndNode(15, 5);
am->AddEdge(5,5,10,15);
am->AddEdge(5,5,10,0);
am->AddEdge(10,0,15,5);
am->AddEdge(10,15,15,5);
am->PrintStateGrid();
am->PrintPheroTable();
	

cout << "FIN" << endl;
return 0;
}
