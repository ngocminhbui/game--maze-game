#pragma once
#include "Defs_Libs.h"
#include "IMapObject.h"
#include "IArtifact.h"
#include "Notification.h"

//singleton 
class Player{
private:
	static Player* _instance;

	//Player data
	vector<IMapObject*> _balo;
	int _baloWeight;

	string _name;
	int _level;
	int _totalMove;
	int _score;
	Player();
	Player(string name, int score = 0, int level = 1);
	
public:
	static void deleteInstance();
	static void createPlayer(string name, int level = 1);
	static Player* getInstance();
	int nextMove();

	string getName();

	int getTotalMove();
	int getScore(bool isWon);
	void setScore(int score);
	int getLevel();
	int getBaloWeight();
	int getNArtifact();
	void showBackpack();
	bool pushArtifact(IMapObject* artifact);
	~Player();
};