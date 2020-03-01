#include <iostream>
#include "PheroEntry.h"

using namespace std;

PheroEntry::PheroEntry(){
	
}

PheroEntry::PheroEntry(PheroKey new_key, double new_value){
	key = new_key;
	value = new_value;
}

PheroEntry::PheroEntry( const PheroEntry& entry){
	key = entry.GetKey();
	value = entry.GetValue();
}

PheroKey PheroEntry::GetKey() const{
	return key;
}

double PheroEntry::GetValue() const{
	return value;
}

bool PheroEntry::operator==(const PheroEntry& entry){
	if(key == entry.GetKey() && value == entry.GetValue()){
		return true;
	} else {
		return false;
	}
}

ostream& operator<<(ostream& out, const PheroEntry& entry){
	return out << entry.GetKey() << ": " << entry.GetValue() << endl;
}
