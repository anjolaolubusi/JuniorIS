#include <iostream>
#include "SmartPtr.h"
#include "GraphMap.h"
#include "PheroKey.h"
#include <string>
#include <map>

using namespace std;

int main(){
SmartPtr<string> test_string(new string());
*test_string = "Ground Control to Major Tom";
cout << *test_string << endl;
GraphMap am;
am.SetStartNode(5,5);
am.SetEndNode(15, 5);
am.AddNode(5,5,10,15);
am.AddNode(5,5,10,0);
am.AddNode(10,0,15,5);
am.AddNode(10,15,15,5);
am.PrintStateGrid();
am.PrintPheroTable();
am.GetAllEdges(5,5);

return 0;
}
