#include "Map.h"
#include "GameConfig.h"
#include "GameController.h"
int main(){
	string temp;
	bool continueGame = true;
	while (continueGame){
		GameController::createInstance("appconfig.csv");
		continueGame=GameController::getInstance()->run();
		GameController::deleteInstance();
	}
}