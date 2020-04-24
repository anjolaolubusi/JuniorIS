#include "MMAS.h"
using namespace std;


//TODO: Added Error Checks

int main()
{

MMAS am;
am.SetStartNode(200,400);
am.SetEndNode(700, 400);
am.AddNode(450, 250);
am.AddNode(450, 800);
am.AddNode(450, 400);
//am.AddEdge(200,400,700,400);
am.AddEdge(200,400,450,250);
am.AddEdge(450,250,700,400);
am.AddEdge(200,400,450,800);
am.AddEdge(450,800,700,400);
am.AddEdge(200, 400, 450, 400);
am.AddEdge(450, 400, 700, 400);

/*am.AddEdge(5,5,10,15);
am.AddEdge(5,5,10,0);
am.AddEdge(10,0,15,5);
am.AddEdge(10,15,15,5);*/
//am.PrintPheroTable();
am.run();

cout << "FIN" << endl;
return 0;
}
