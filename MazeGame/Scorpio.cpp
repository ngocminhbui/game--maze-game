#include "Scorpio.h"
#include "Map.h"
int Scorpio::sightRange = 4;
int Scorpio::moveRange = 1;


Scorpio::Scorpio(pair<int, int> pos):IMonster(pos){
	_position = pos;
}
string Scorpio::getType(){
	return "scorpio";
}
DrawCommand Scorpio::draw(){
	return DrawCommand(_position, _color, stoi(GameConfig::getConfig("backgroundColor")), 'C');
}

bool Scorpio::canSee(pair<int, int> human){
	int toX = human.first;
	int toY = human.second;
	int fromX = _position.first;
	int fromY = _position.second;
	
	float test = float((toX - fromX)) / (fromY - toY);
	if (test != 1.0 && test != -1.0)
		return false;

	int range = Scorpio::sightRange;

	if (fromX < toX && fromY < toY){
		while (range--){
			fromX++;
			fromY++;
			if (fromX == toX && fromX == toX)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromX)) == true)
				return false;
		}
	}
	else if (fromX > toX && fromY > toY){
		while (range--){
			fromX--;
			fromY--;
			if (fromX == toX && fromX == toX)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromX)) == true)
				return false;
		}
	}
	else if (fromX > toX && fromY < toY){
		while (range--){
			fromX--;
			fromY++;
			if (fromX == toX && fromX == toX)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromX)) == true)
				return false;
		}
	}
	else
	{
		while (range--){
			fromX++;
			fromY--;
			if (fromX == toX && fromX == toX)
				return true;
			if (Map::getInstance()->isBlock(pair<int, int>(fromX, fromX)) == true)
				return false;
		}
	}

	return false;
}

int Scorpio::findHuman(pair<int, int> human){
	int toX = human.first;
	int toY = human.second;
	int fromX = _position.first;
	int fromY = _position.second;

	if (fromX < toX && fromY < toY && Map::getInstance()->verifyMove(fromX + 1, fromY + 1) == true)
		return DOWN_RIGHT;
	else if (fromX < toX && fromY > toY&& Map::getInstance()->verifyMove(fromX + 1, fromY - 1) == true)
		return DOWN_LEFT;
	else if (fromX > toX && fromY < toY&& Map::getInstance()->verifyMove(fromX - 1, fromY + 1) == true)
		return UP_RIGHT;
	else if (fromX > toX && fromY > toY&& Map::getInstance()->verifyMove(fromX - 1, fromY - 1) == true)
		return UP_LEFT;
	else return STAY;

}
pair<int, int> Scorpio::updateState(pair<int, int> humanPosition){
	pair<int, int> nextMove = _position;

	if (this->canSee(humanPosition) == true){
		int k = findHuman(humanPosition);
		if (k == DOWN_RIGHT) { nextMove.first++;			nextMove.second++; }
		else if (k == DOWN_LEFT) { nextMove.first++;			nextMove.second--; }
		else if (k == UP_RIGHT) { nextMove.first--;			nextMove.second++; }
		else if (k == UP_LEFT) { nextMove.first--;			nextMove.second--; }

		if (nextMove == humanPosition)
			return nextMove;

		k = findHuman(humanPosition);
		if (k == DOWN_RIGHT) { nextMove.first++;			nextMove.second++; }
		else if (k == DOWN_LEFT) { nextMove.first++;			nextMove.second--; }
		else if (k == UP_RIGHT) { nextMove.first--;			nextMove.second++; }
		else if (k == UP_LEFT) { nextMove.first--;			nextMove.second--; }
	}
	else{
		int dx[] = { 1, -1, 1, -1 };
		int dy[] = { 1, -1, -1, 1 };
		int i = rand() % 4;
		if (Map::getInstance()->verifyMove(nextMove.first + dx[i], nextMove.second + dy[i]) == true){
			nextMove.first += dx[i];
			nextMove.second += dy[i];
		}

	}
	return nextMove;
}