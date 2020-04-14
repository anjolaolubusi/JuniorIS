/*#include "GraphMap.h"
#include "Ant.h"*/

#include "PheroKey.h"

using namespace std;

int main(){
/*
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
am.PrintPheroTable();//
int ant_cout = 10;
Ant ants[ant_cout];

for(int i=0; i < ant_cout; i++){
ants[i] = Ant(am.GetStartNode());
}

for(int i = 0; i < ant_cout; i++){
ants[i].MoveAntToEndNode(am, true);
}

for(int iter = 0; iter < 15; iter++){
	for(int i = 0; i < ant_cout; i++){
		while(ants[i].GetX() != am.GetEndNode().first && ants[i].GetY() != am.GetEndNode().second){
			ants[i].MoveAntToEndNode(am);
		}
	}

	for(int i = 0; i < ant_cout; i++){
		do{
		ants[i].MoveAntToStartNode(am);
		}while(ants[i].GetX() != am.GetStartNode().first && ants[i].GetY() != am.GetStartNode().second);
	}

	for(int i=0; i < ant_cout; i++){
		ants[i].EmptyNV();
	}	

am.EvapouratePhero(.8);
cout << "Best Path: ";
set<PheroKey> jdhd =  am.FindBestPathOfIter();
set<PheroKey>::iterator best_itr;
for(best_itr=jdhd.begin(); best_itr != jdhd.end(); best_itr++){
	cout << *best_itr << " ";
}
cout << endl;

}


cout << "Best Path: ";
set<PheroKey> jdhd =  am.FindBestPathOfIter();
set<PheroKey>::iterator best_itr;
for(best_itr=jdhd.begin(); best_itr != jdhd.end(); best_itr++){
	cout << *best_itr << " ";
}
cout << endl;
*/

PheroKey key = PheroKey(4,6,2,1);
cout << key.GetPoint1()[1] << endl;

return 0;
}
