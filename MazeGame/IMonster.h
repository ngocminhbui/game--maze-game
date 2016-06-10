#pragma once
#include "IMapMovingObject.h"
class IMonster :public IMapMovingObject{
protected:
	static int _color;
public:
	IMonster(pair<int, int> position);
	static void setColor(int color);
	virtual pair<int, int> updateState(pair<int,int> humanPosition)=0;
};

