#ifndef PHEROENTRY_H
#define PHEROENTRY_H
#include <iostream>
#include "PheroKey.h"

class PheroEntry{
private:
	PheroKey key;
	double value;
public:
	PheroEntry();
	PheroEntry(PheroKey key, double value);
	PheroEntry(const PheroEntry& otherentry);
	PheroKey GetKey() const;
	double GetValue() const;
	bool operator ==(const PheroEntry& entry);
	friend std::ostream& operator<<(std::ostream& out, const PheroEntry& entry);
};
#endif
