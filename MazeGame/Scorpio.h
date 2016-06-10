#pragma once
#include "IMonster.h"

class Scorpio :public IMonster{
public:
	static int sightRange;
	static int moveRange;
public:
	Scorpio(pair<int, int> pos);
	string getType();
	virtual DrawCommand draw();

	bool canSee(pair<int, int> human);
	int findHuman(pair<int, int> humanPosition);
	virtual pair<int, int> updateState(pair<int, int> humanPosition);
	
};