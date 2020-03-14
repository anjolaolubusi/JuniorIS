#ifndef PHEROKEYHASH_H
#define PHEROKEYHASH_H

#include "PheroKey.h"

class PheroKeyHash{
public:
	size_t operator()(const PheroKey& key) const{ 
        return key.GetDistanceBetweenPoints() + sqrt( pow((key.GetPoint2().first), 2.0) + pow((key.GetPoint2().second), 2)) + sqrt( pow((key.GetPoint1().first), 2.0) + pow((key.GetPoint1().second), 2)); 
    } 
};
#endif
