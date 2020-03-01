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
am.ChangeState(10,3, "N");
am.ChangeState(15, 5, "F");
am.ChangeState(10,15, "N");
am.PrintPheroGrid();
am.PrintStateGrid();
PheroKey key1 = PheroKey(pair<int, int>(1,2), pair<int, int>(3,4));
PheroKey key2 = PheroKey(pair<int, int>(6,6), pair<int, int>(7,2));
cout << key1 << endl;
cout << key2 << endl;

return 0;
}
