#include "Map.h"
//singleton
Map* Map::_instance = NULL;


Map* Map::createInstance(int level){
	if (Map::_instance == NULL)
		Map::_instance = new Map(level);
	return Map::_instance;
}

Map* Map::getInstance(){
	return Map::_instance;
}

//end singleton


vector<IMapObject*>& Map::operator[](int x){
	return _map[x];
}
IMapObject*& Map::operator()(int first, int second){
	return _map[first][second];
}
IMapObject*& Map::operator()(pair<int, int> position){
	return _map[position.first][position.second];
}

bool Map::verifyMove(int x, int y){
	if (_instance->allowedPosition(pair<int, int>(x, y)) == false)
		return false;
	return	_instance->isSpace(pair<int, int>(x, y)) == true;
}


void Map::setObject(IMapObject* object, pair<int, int> pos){
	_map[pos.first][pos.second] = object;
}

vector<vector<IMapObject*>>& Map::getMap(){
	return _map;
}

int Map::getNFree(){
	int count = 0;
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			if (isBlock(pair<int, int>(i, j)) == false)
				count++;
	return count;
}

vector<IMapMovingObject*> Map::getMovingObject(){
	vector <IMapMovingObject*> result;
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			if (isMonster(pair<int, int>(i, j)) == true)
				result.push_back(((IMapMovingObject*)(*this)(i, j)));
	return result;
}



Map::Map(int level){
	generateMap(level);
}


int Map::getWidth(){
	return _mapWidth;
}
int Map::getHeight(){
	return _mapHeight;
}

//Pair tính theo tọa độ mảng
bool Map::allowedPosition(pair<int, int> p){
	if (p.first >= 0 && p.second >= 0 && p.first < _mapWidth && p.second < _mapHeight)
		return true;
	else return false;
}


void Map::generateMap(int level){
	//parse right level
	int maxLevel = stoi(GameConfig::getConfig("maxLevel"));
	level = level % maxLevel;
	if (level == 0) level = maxLevel-1;

	//generate width and height
	this->_mapHeight = rand() % stoi(GameConfig::getConfig("maxHeight")) + stoi(GameConfig::getConfig("minHeight"));
	this->_mapWidth = rand() % stoi(GameConfig::getConfig("maxWidth")) + stoi(GameConfig::getConfig("minWidth"));

	//create objects map
	_map.resize(_mapWidth);
	for (int i = 0; i < _mapWidth; i++)
		_map[i].resize(_mapHeight, NULL);

	//create objects
	//do{
		generateMapBlock(maxLevel - level);
	//} while (checkConnectedMap() == true);

	generateMonster(maxLevel - level);
	generateArtifact(maxLevel - level);
	generateStartEnd();
}


bool Map::isSpace(pair<int, int> position){
	return allowedPosition(position)== true && _map[position.first][position.second] == NULL;
}
bool Map::isBlock(pair<int, int> position){
	return allowedPosition(position) == true && _map[position.first][position.second] != NULL && _map[position.first][position.second]->getType() == "block";
}
bool Map::isArtifact(pair<int, int> position){
	if (allowedPosition(position) == false)
		return false;
	if (_map[position.first][position.second] == NULL)
		return false;
	string type = _map[position.first][position.second]->getType();
	return (type == "weapon" || type == "jewelry" || type == "stuff" || type == "statue");
}
bool Map::isMonster(pair<int, int> position){
	if (allowedPosition(position) == false)
		return false;
	if (_map[position.first][position.second] == NULL)
		return false;
	string type = _map[position.first][position.second]->getType();
	return (type == "mummy" || type == "scorpio" || type == "zombie");
}

bool Map::isEndPort(pair<int, int> position){
	return position == _mapEnd;
}

void Map::generateMapBlock(int density){
	//tạo walls bao quanh
	for (int i = 0; i < _mapHeight; i++){
		_map[0][i] = new Block(pair<int, int>(0, i));
		_map[_mapWidth - 1][i] = new Block(pair<int, int>(_mapWidth - 1, i));
	}
	for (int i = 1; i < _mapWidth-1; i++){
		_map[i][0] = new Block(pair<int, int>(i, 0));
		_map[i][_mapHeight - 1] = new Block(pair<int, int>(i, _mapHeight - 1));
	}

	//tạo block bên trong
	int nBlock = (_mapWidth - 2)*(_mapHeight - 2) / density;
	int m, n;
	for (int i = 0; i < nBlock; i++){
		do{
			m = rand() % _mapWidth;
			n = rand() % _mapHeight;
		} while (allowedPosition(pair<int, int>(m, n)) == false || isSpace(pair<int, int>(m, n)) == false);
		_map[m][n] = new Block(pair<int,int>(m,n));
	}
}
void Map::generateArtifact(int density){
	int nArtifact = (_mapWidth - 2)*(_mapHeight - 2) / density;
	int m, n;
	for (int i = 0; i < nArtifact; i++){
		do{
			m = rand() % _mapWidth;
			n = rand() % _mapHeight;
		} while (allowedPosition(pair<int, int>(m, n)) == false || isSpace(pair<int, int>(m, n)) == false);
		int kind = rand() % 4;
		if (kind == 0)
			_map[m][n] = new Jewelry(pair<int, int>(m, n));
		else if (kind == 1)
			_map[m][n] = new Weapon(pair<int, int>(m, n));
		else if (kind == 2)
			_map[m][n] = new Statue(pair<int, int>(m, n));
		else if (kind == 3)
			_map[m][n] = new Stuff(pair<int, int>(m, n));
	}

}
void Map::generateMonster(int density){
	int nMonster = (_mapWidth - 2)*(_mapHeight - 2) / density;
	int m, n;
	for (int i = 0; i < nMonster; i++){
		do{
			m = rand() % _mapWidth;
			n = rand() % _mapHeight;
		} while (allowedPosition(pair<int, int>(m, n)) == false || isSpace(pair<int, int>(m, n)) == false);
		int kind = rand() % 3;
		if (kind == 0)
			_map[m][n] = new Mummy(pair<int, int>(m, n));
		else if (kind == 1)
			_map[m][n] = new Scorpio(pair<int, int>(m, n));
		else if (kind == 2)
			_map[m][n] = new Zombie(pair<int, int>(m, n));
	}
}
void Map::generateStartEnd(){
	do{
		do{
			_mapStart.first = rand() % _mapWidth;
			_mapStart.second = rand() % _mapHeight;
		} while (allowedPosition(_mapStart) == false || isSpace(_mapStart) == false);
		do{
			_mapEnd.first = rand() % _mapWidth;
			_mapEnd.second = rand() % _mapHeight;
		} while (allowedPosition(_mapEnd) == false || isSpace(_mapEnd) == false);
	} while (_mapStart == _mapEnd);
}
bool Map::checkConnectedMap(){
	Map* map = Map::getInstance();
	
	vector<vector<bool>> mark;
	int w = _mapWidth;
	int h = _mapHeight;

	//Khởi tạo mảng đánh dấu
	mark.resize(w);
	for (int i = 0; i < w; i++)
		mark[i].resize(h, false);

	//Khởi tạo mảng điều hướng
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	//Khởi tạo queue
	queue<pair<int, int>> s;

	//BFS
	s.push(_mapStart);
	mark[_mapStart.first][_mapStart.second] = true;

	bool isFound = false;
	pair<int, int> next;
	while (s.empty() == false && isFound == false){
		next = s.front();
		s.pop();

		if (next == _mapEnd){
			isFound = true;
			break;
		}

		for (int i = 0; i < 4; i++){
			pair<int, int> con = pair<int, int>(next.first + dx[i], next.second + dy[i]);
			if (map->allowedPosition(con) == true && map->isBlock(con) == false && mark[con.first][con.second] == false){
				s.push(con);
				mark[con.first][con.second] = true;
			}
		}
	}

	return isFound;
}

Map::~Map()
{
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			delete _map[i][j];
}


pair<int, int> Map::getStartPoint(){
	return _mapStart;
}

pair<int, int> Map::getEndPoint(){
	return _mapEnd;
}

//for save game
vector<vector<char>> Map::getCharMap(){
	vector<vector<char>> charMap;
	charMap.resize(_mapWidth);
	for (int i = 0; i < _mapWidth; i++)
		charMap[i].resize(_mapHeight,' ');
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			if (_map[i][j] == NULL)
				charMap[i][j] = ' ';
			else 
				charMap[i][j]=_map[i][j]->draw().character;
	return charMap;
}