#include "Stuff.h"
#include "IArtifact.h"
#include "GameController.h"

Stuff::Stuff(pair<int, int> pos):IArtifact(pos){
	_usefulness = rand() % 1000;
}

string Stuff::getType(){
	return "stuff";
}
string Stuff::getName(){
	return "stuff";
}

string Stuff::getInformation(){
	ostringstream oss;
	oss << "Stuff, usefulness: " << _usefulness << ", weight: " << getMass() << "g" << ".";
	return oss.str();
}