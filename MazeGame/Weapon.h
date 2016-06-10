#pragma once
#include "IArtifact.h"
class Weapon :public IArtifact{
private:
	int _antiPersonal;
public:
	Weapon(pair<int, int> pos);
	string getType();
	virtual string getName();

	virtual int getAntiPersonal();


	virtual string getInformation();
};