#pragma once
#include "Defs_Libs.h"
#include "IMapStaticObject.h"

class IArtifact :public IMapStaticObject{
protected:
	static int _color;
	static char _representChar;

	int _mass;
	float _year;
public:
	IArtifact(pair<int, int> position);

	int getMass();
	float getBornYear();
	
	float getYearOld();

	static void setColor(int color);
	DrawCommand draw();
	virtual string getName() = 0;
	virtual string getInformation() = 0;
}; 

