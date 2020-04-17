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
am.PrintPheroTable();
cout << endl;

/*am.PrintPheroTable();
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
*/
int ant_cout = 2;
Ant ants[ant_cout];

//for(int inter = 0; inter < 1; inter++){

for (int i=0; i < ant_cout; i++){
	ants[i] = Ant(am.GetStartX(), am.GetStartY());
	cout << "DD" << endl;
	ants[i].MoveAntToEndNode(am, true);
	while(ants[i].GetX() != am.GetEndX() && ants[i].GetY() != am.GetEndY()){
	ants[i].MoveAntToEndNode(am);
	}
	ants[i].PrintAntInfo(am);
}

//}




/*
cout << "Best Path: ";
set<PheroKey> jdhd =  am.FindBestPathOfIter();
set<PheroKey>::iterator best_itr;
for(best_itr=jdhd.begin(); best_itr != jdhd.end(); best_itr++){
	cout << *best_itr << " ";
}
cout << endl;
*/


cout << "FIN" << endl;
return 0;
}
