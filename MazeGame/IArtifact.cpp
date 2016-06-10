#include "IArtifact.h"
#include "GameController.h"
int IArtifact::_color;
char IArtifact::_representChar = 'o';

void IArtifact::setColor(int color){
	_color = color;
}

DrawCommand IArtifact::draw(){
	return DrawCommand(_position, _color, stoi(GameConfig::getConfig("backgroundColor")), 'o');
}

IArtifact::IArtifact(pair<int, int> position) :IMapStaticObject(position){
	_mass = rand() % (stoi(GameConfig::getConfig("maxArtifactWeight")) - stoi(GameConfig::getConfig("minArtifactWeight"))) + stoi(GameConfig::getConfig("minArtifactWeight"));
	_year = rand() % stoi(GameConfig::getConfig("gameYear"));
}

int IArtifact::getMass(){
	return _mass;
}

float IArtifact::getBornYear(){
	return _year;
}

float IArtifact::getYearOld(){
	return GameController::getInstance()->getCurrentYear() - _year;
}
