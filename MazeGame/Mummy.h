#pragma once
#include "IMonster.h"

class Mummy :public IMonster{
private:
	static int sightRange;
	static int moveRange;
public:
	Mummy(pair<int, int> pos);
	string getType();

	virtual DrawCommand draw();
	bool canSee(pair<int, int> human);
	int findHuman(pair<int, int> humanPosition);
	virtual pair<int, int> updateState(pair<int, int> humanPosition);
};