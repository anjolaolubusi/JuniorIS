#ifndef PHEROTABLE_H
#define PHEROTABLE_H

#include "PheroKey.h"

class PheroTable{
private:
	PheroKey** keys;
	double** values;
public:
	PheroTable();
	double get(const PheroKey& key);
	void insert(const PheroKey& key, const double value);
	void remove(const PheroKey& key);
	~PheroTable();
};

#endif
