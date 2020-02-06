#include <iostream>
#include "SmartPtr.h"
#include <string>

using namespace std;

int main(){
SmartPtr<string> test_string(new string());
*test_string = "Ground Control to Major Tom";
cout << *test_string << endl;
}
