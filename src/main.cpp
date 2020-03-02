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
am.ChangeState(5,5,"S");
am.UpdatePhero(5,5,10,3,1);
am.ChangeState(10,3, "N");
am.UpdatePhero(5,5,15,5,14);
am.ChangeState(15, 5, "F");
am.ChangeState(10,15, "N");
am.PrintStateGrid();
am.PrintPheroTable();

return 0;
}
