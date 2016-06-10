#include "Jewelry.h"
#include "IArtifact.h"
#include "GameController.h"

Jewelry::Jewelry(pair<int, int> pos):IArtifact(pos){
	char material[] = { GOLD, SILVER, COPPER };
	_material = material[rand() % 3];
}
string Jewelry::getType(){
	return "jewelry";
}

string Jewelry::getName(){
	return "jewelry";
}

float Jewelry::getCurrentStrong(){
	float k;
	if (_material == GOLD)
		k = 1000;
	else if (_material == SILVER)
		k = 800;
	else k = 300;
	int nYear = GameController::getInstance()->getCurrentYear() - _year;
	return k - k*nYear*0.000001;
}

string Jewelry::getMaterial(){
	if (_material == GOLD){
		return "Gold";
	}
	else if (_material == SILVER){
		return "Silver";
	}
	else
		return "Copper";
}
float Jewelry::getLostStrong(){
	int nYear = GameController::getInstance()->getCurrentYear() - _year;
	if (_material == GOLD)
		return nYear*0.000001 * 1000;
	else if (_material == SILVER)
		return nYear*0.000001 * 800;
	else return nYear*0.000001 * 300;
}

float Jewelry::getFixPrice(){
	return getLostStrong() * 200;
}

string Jewelry::getInformation(){
	ostringstream outStream;
	if (_material == COPPER)
		outStream << "Jewelry, " << getMaterial() << ", " << getYearOld() << " years old, " << "weight: " << getMass() << "g" << ", fixPrice:" << "$" << getFixPrice();
	else
		outStream << "Jewelry, " << getMaterial() << ", " << getYearOld() << " years old, " << "weight: " << getMass() << "g" << " fixPrice:" << "$" << getFixPrice() << "+0.2l gas";
	return outStream.str();
}