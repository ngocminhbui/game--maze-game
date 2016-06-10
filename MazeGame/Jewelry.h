#pragma once
#include "IArtifact.h"
class Jewelry :public IArtifact{
private:
	int _material;
public:
	Jewelry(pair<int, int> pos);
	string getType();
	virtual string getName();
	virtual float getCurrentStrong();
		
	virtual string getMaterial();
	virtual float getLostStrong();

	virtual float getFixPrice();

	virtual string getInformation();
};