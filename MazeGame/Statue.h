#pragma once
#include "IArtifact.h"
class Statue :public IArtifact{
private:
	string _statueName;
public:
	Statue(pair<int, int> pos);
	string getType();
	virtual string getName();

	virtual string getInformation();
};