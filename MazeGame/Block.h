#pragma once
#include "Defs_Libs.h"
#include "IMapObject.h"

class Block:public IMapObject{
private:
	static int _color;
	Block();
public:
	static void setColor(int color);

	Block(pair<int, int> position);

	string getType();

	DrawCommand draw();
};