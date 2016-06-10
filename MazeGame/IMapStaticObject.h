#pragma once
#include "IMapObject.h"
class IMapStaticObject:public IMapObject{
public:
	IMapStaticObject(pair<int, int> position) :IMapObject(position){
	}
	virtual string getType() = 0;
	virtual DrawCommand draw() = 0;
};