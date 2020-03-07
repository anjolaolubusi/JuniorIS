#include "GraphMap.h"
#include "Ant.h"

using namespace std;

int main(){
GraphMap am;
am.SetStartNode(5,5);
am.SetEndNode(15, 5);
am.AddNode(5,5,10,15);
am.AddNode(5,5,10,0);
am.AddNode(10,0,15,5);
am.AddNode(10,15,15,5);
am.PrintStateGrid();
//am.PrintPheroTable();
Ant anthoy = Ant(5,5);
anthoy.MoveAntToEndNode(am, true);
anthoy.MoveAntToEndNode(am);
cout << anthoy << endl;
am.PrintPheroTable();
anthoy.MoveAntToStartNode(am);
anthoy.MoveAntToStartNode(am);
am.PrintPheroTable();
cout << anthoy << endl;
am.EvapouratePhero();
am.PrintPheroTable();
return 0;
}
