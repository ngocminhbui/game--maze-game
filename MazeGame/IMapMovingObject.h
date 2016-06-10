#pragma once
#include "IMapObject.h"

class IMapMovingObject:public IMapObject{
public:
	IMapMovingObject(pair<int, int> position);
	virtual string getType() = 0;
	virtual DrawCommand draw() = 0;
	virtual pair<int, int> updateState(pair<int, int> humanPosition) = 0;
};