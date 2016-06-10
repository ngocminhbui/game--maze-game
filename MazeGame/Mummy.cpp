#include "Mummy.h"
#include "Map.h"

int Mummy::sightRange = 4;
int Mummy::moveRange = 1;

Mummy::Mummy(pair<int, int> pos):IMonster(pos){
}
string Mummy::getType(){
	return "mummy";
}
DrawCommand Mummy::draw(){
	return DrawCommand(_position, _color, stoi(GameConfig::getConfig("backgroundColor")), 'M');
}

bool Mummy::canSee(pair<int, int> human){
	int toX = human.first;
	int toY = human.second;
	int fromX = _position.first;
	int fromY = _position.second;
	
	if (fromX != toX && fromY != toY)
		return false;
	
	int sight = Mummy::sightRange;

	if (fromX == toX && fromY < toY){
		while (sight--){
			fromY++;
			if (fromY == toY)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromY)) == true)
				return false;
		}
	}
	else if (fromX == toX && fromY>toY){
		while (sight--){
			fromY--;
			if (fromY == toY)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromY)) == true)
				return false;
		}
	}
	else if (fromY == toY && fromX > toX){
		while (sight--){
			fromX--;
			if (fromX == toX)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromY)) == true)
				return false;
		}
	}
	else{
		while (sight--){
			fromX++;
			if (fromX == toX)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromY)) == true)
				return false;
		}
	}

	return false;
}



int Mummy::findHuman(pair<int, int> humanPosition){
	if (_position.first < humanPosition.first && Map::getInstance()->verifyMove(_position.first + 1, _position.second) == true)
		return RIGHT;
	else if (_position.first > humanPosition.first && Map::getInstance()->verifyMove(_position.first - 1, _position.second) == true)
		return LEFT;
	else if (_position.second < humanPosition.second && Map::getInstance()->verifyMove(_position.first, _position.second + 1) == true)
		return DOWN;
	else if (_position.second > humanPosition.second && Map::getInstance()->verifyMove(_position.first, _position.second - 1) == true)
		return UP;
	else return STAY;
}


pair<int, int> Mummy::updateState(pair<int, int> humanPosition){
	pair<int, int> nextMove = _position;
	//return nextMove;
	if (this->canSee(humanPosition) == true){
		int k = findHuman(humanPosition);
		if (k == UP) nextMove.second--;
		else if (k == DOWN) nextMove.second++;
		else if (k == LEFT) nextMove.first--;
		else if (k == RIGHT) nextMove.first++;

		if (nextMove == humanPosition)
			return nextMove;
	
		k = findHuman(humanPosition);
		if (k == UP) nextMove.second--;
		else if (k == DOWN) nextMove.second++;
		else if (k == LEFT) nextMove.first--;
		else if (k == RIGHT) nextMove.first++;
	}
	else{ 
		int dx[] = { 0, 1, 0, -1 };
		int dy[] = { 1, 0, -1, 0 };
		int i = rand() % 4;
		if (Map::getInstance()->verifyMove(nextMove.first + dx[i], nextMove.second + dy[i]) == true){
			nextMove.first += dx[i];
			nextMove.second += dy[i];
		}
		
	}
	return nextMove;
}