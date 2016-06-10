#include "Weapon.h"
#include "GameController.h"
Weapon::Weapon(pair<int, int> pos) :IArtifact(pos){
	_antiPersonal = rand() % 100;
}
string Weapon::getType(){
	return "weapon";
}
string Weapon::getName(){
	return "Weapon";
}

int Weapon::getAntiPersonal(){
	return _antiPersonal;
}


string Weapon::getInformation(){
	ostringstream outStream;
	outStream << "Weapon, " << "antiPersonal: " << getAntiPersonal() << " , years old:" << getYearOld() << ", weight:" << getMass()<<"g";
	return outStream.str();
}