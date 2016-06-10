#pragma once
#include "IArtifact.h"
class Stuff :public IArtifact{
private:
	int _usefulness;
public:
	Stuff(pair<int, int> pos);
	
	string getType();
	virtual string getName();

	virtual string getInformation();
};