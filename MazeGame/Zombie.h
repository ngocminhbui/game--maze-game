#pragma once
#include "IMonster.h"

class Zombie :public IMonster{
private:
private:
	static int MsightRange;
	static int SsightRange;
	static int moveRange;
public:
	Zombie(pair<int, int> pos);
	string getType();
	virtual DrawCommand draw();

	bool canSee(pair<int, int> human);
	int findHuman(pair<int, int> humanPosition);
	virtual pair<int, int> updateState(pair<int, int> humanPosition);

	bool Zombie::scorpioSee(pair<int, int> human);
	bool Zombie::mummySee(pair<int, int> human);
};