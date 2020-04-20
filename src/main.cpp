#include "GraphMap.h"
#include "Ant.h"

using namespace std;


int main(void){

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

int ant_cout = 100;
Ant ants[ant_cout];

for(int inter = 0; inter < 50; inter++){

for (int i=0; i < ant_cout; i++){
	ants[i] = Ant(am.GetStartX(), am.GetStartY());
	ants[i].MoveAntToEndNode(am, true);
	while(ants[i].GetX() != am.GetEndX() && ants[i].GetY() != am.GetEndY()){
	ants[i].MoveAntToEndNode(am);
	}

}

//Add logic to get best path of iteration

int choice_index = -1;
double MaxInfo = -99999.0;
double test_value = 0;
for(int i =0; i < ant_cout; i++){
	test_value = ants[i].GetValueOfPath();
	if(MaxInfo < test_value){
		MaxInfo = test_value;
		choice_index = i;
	}
}

am.SetBestPath(ants[choice_index].GetKeysVisited());
am.EvapouratePhero();
am.UpdatePhero(inter);

for(int i=0; i < ant_cout; i++){
	ants[i].EmptyKV();
}

}

cout << "FINAL"  << endl;
am.PrintPheroTable();


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
