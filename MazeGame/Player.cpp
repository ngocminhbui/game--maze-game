#include "Player.h"
#include "Map.h"
Player* Player::_instance;

Player::Player(string name, int score , int level ){
	_name = name;
	_score = score;
	_level = level;
	_totalMove = 0;
	_baloWeight = 0;
}


int Player::getScore(bool isWon){
	if (isWon == false)
		return 0;
	else{
		int nFree = Map::getInstance()->getNFree();
		int k = 3 * nFree - _totalMove;
		return (k > 0) ? k : 0;
	}
}

void Player::setScore(int score){
	_score = score;
}

void Player::deleteInstance(){
	delete _instance;
	_instance = NULL;
}
void Player::createPlayer(string name, int level ){
	_instance = new Player(name, level);
}
Player* Player::getInstance(){
	return _instance;
}
int Player::nextMove(){

	int arrow = -1;
	_flushall();
	GraphicFuntions::flushInput();
	do{
		GraphicFuntions::flushInput();
		if (GetAsyncKeyState(VK_UP))
			arrow = UP;
		GraphicFuntions::flushInput();
		if (GetAsyncKeyState(VK_DOWN))
			arrow = DOWN;
		GraphicFuntions::flushInput();
		if (GetAsyncKeyState(VK_LEFT))
			arrow = LEFT;
		GraphicFuntions::flushInput();
		if (GetAsyncKeyState(VK_RIGHT))
			arrow = RIGHT;
		GraphicFuntions::flushInput();
	} while (arrow == -1);
	GraphicFuntions::flushInput();
	_totalMove++;
	return arrow;
}

string Player::getName(){
	return _name;
}


int Player::getTotalMove(){
	return _totalMove;
}
int Player::getLevel(){
	return _level;
}
int Player::getBaloWeight(){
	return _baloWeight;
}
int Player::getNArtifact(){
	return _balo.size();
}
void Player::showBackpack(){
	Notification* noti = Notification::getInstance();
	noti->announce("Your backpark items:");
	for (int i = 0; i < _balo.size(); i++){
		IArtifact* obj = (IArtifact*)_balo[i];
		noti->announce(obj->getInformation());
	}
	ostringstream oss;
	oss << "Total weight:" << _baloWeight;
	noti->announce(oss.str());
}
bool Player::pushArtifact(IMapObject* artifact){
	IArtifact* p = (IArtifact*)artifact;
	if (p->getMass() + _baloWeight <= 50000){
		_balo.push_back(p);
		_baloWeight += p->getMass();
		return true;
	}
	return false;
}
Player::~Player(){
	for (int i = 0; i < _balo.size(); i++)
		delete _balo[i];
}