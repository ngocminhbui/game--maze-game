#include "IMonster.h"
#include "Map.h"
int IMonster::_color;

IMonster::IMonster(pair<int, int> position) :IMapMovingObject(position){

}

void IMonster::setColor(int color){
	_color = color;
}
