#include "MMAS.h"
using namespace std;

int main()
{

MMAS am;

//Sets Start Node
am.SetStartNode(200,400);
//Sets End Node
am.SetEndNode(700, 400);

//Creates Graph
am.AddNode(450, 250);
am.AddNode(450, 800);
am.AddNode(450, 400);
am.AddEdge(200,400,450,250);
am.AddEdge(450,250,700,400);
am.AddEdge(200,400,450,800);
am.AddEdge(450,800,700,400);
am.AddEdge(200, 400, 450, 400);
am.AddEdge(450, 400, 700, 400);

//Launches Application
am.run();

cout << "FIN" << endl;
return 0;
}
