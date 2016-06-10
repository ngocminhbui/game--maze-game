#pragma once
#include "Map.h"
#include "GameConfig.h"
#include "GraphicFunctions.h"
#include "Notification.h"
#include "Utils.h"

#include "Block.h"

#include "IArtifact.h"
#include "Jewelry.h"
#include "Weapon.h"

#include "IMonster.h"
#include "Mummy.h"
#include "Zombie.h"
#include "Scorpio.h"

#include "Player.h"

class GameController{
private:
	//instance
	static GameController* _instance;

	//Controller data
	int _year;
	int _gameTurn;


	//singleton
	GameController(){};
	GameController(string configFile);

	~GameController(){
		Map::deleteInstance();
		Player::deleteInstance();
		Notification::deleteInstance();
	}
protected:
	
public:
	int getCurrentYear();

	//gameflow control
	bool run();

	int onGame();

	bool MoveObject(pair<int, int> humanPosition, vector<IMapMovingObject*> & movingObjectList);

	bool MovePlayer(const int Direction, pair<int, int> &origPos);

	void startGame();

	void reConfig();

	int startGameMenu();

	int  endGameMenu();

	bool endGame(bool);

	void highScore(bool isWon, bool toSave);

	void saveMapToFile();

	void setupBaseGame();

	void setupDisplay();

	void displayMap();

	vector<pair<int, int>> findPath(pair<int, int> start, pair<int, int> end);

	void displayPath(vector<pair<int, int>> path);
	void clearPath(vector < pair<int, int>> path);
	
	//singleton and destructor
	static GameController* createInstance(string configFile);
	static GameController* getInstance();
	static void deleteInstance(){
		delete _instance;
		_instance = NULL;
	}
	
};

