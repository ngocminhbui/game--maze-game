#pragma once
#include "Defs_Libs.h"
#include "GameConfig.h"
#include "Utils.h"

class IMapObject{
protected:
	pair <int, int> _position;
public:	
	IMapObject(pair<int, int> position){
		_position = position;
	}


	virtual string getType() = 0;
	virtual DrawCommand draw()=0;
	pair<int, int> getPosition(){
		return this->_position;
	}
	void setPosition(pair<int, int> pos){
		_position = pos;
	}
};