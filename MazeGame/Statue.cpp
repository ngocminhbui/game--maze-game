#include "Statue.h"
#include "IArtifact.h"
#include "GameController.h"

Statue::Statue(pair<int, int> pos):IArtifact(pos){
	int k = rand() % 4;
	if (k == 0)
		_statueName = "Statue of liberty";
	else if (k == 1)
		_statueName = "Statue of pride";
	else if (k == 2)
		_statueName = "Statue of brave";
	else if (k == 3)
		_statueName = "Statue of fogiveness";

}
string Statue::getType(){
	return "statue";
}
string Statue::getName(){
	return "statue";
}


string Statue::getInformation(){
	ostringstream outStream;
	outStream << _statueName << " ," << _year << " years old," << "weight: " << getMass() << "g.";
	return outStream.str();
}