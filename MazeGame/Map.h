#pragma once
#include "Defs_Libs.h"
#include "IMapObject.h"
#include "Block.h"
#include "GameConfig.h"

#include "Jewelry.h"
#include "Weapon.h"
#include "Statue.h"
#include "Stuff.h"

#include "Scorpio.h"
#include "Mummy.h"
#include "Zombie.h"


//singleton
class Map{
private:
	//map data
	vector<vector<IMapObject*>> _map;

	pair<int, int> _mapStart;
	pair<int, int> _mapEnd;

	//map properties
	int _mapWidth;
	int _mapHeight;

	

	//singleton
	static Map* _instance;
	Map(){};
	Map(int level);
	//destructor
	~Map();
public:
	//singleton
	static Map* createInstance(int level);
	static void deleteInstance(){
		delete _instance;
		_instance = NULL;
	}
	static Map* getInstance();
	//end singleton

	//map creators
	void generateMap(int level);
	void generateMapBlock(int density);
	void generateArtifact(int density);
	void generateMonster(int density);
	void generateStartEnd();


	//operator
	vector<IMapObject*>& operator[](int x);
	IMapObject*& operator()(int first, int second);
	IMapObject*& operator()(pair<int, int> position);

	//getter
	vector<vector<IMapObject*>>& getMap();
	vector<vector<char>> getCharMap();
	int getWidth();
	int getHeight();
	int getNFree();
	
	vector<IMapMovingObject*> getMovingObject();
	pair<int, int> getStartPoint();
	pair<int, int> getEndPoint();

	//setter
	void setObject(IMapObject* object, pair<int, int> pos);


	//utils
	bool verifyMove(int x, int y);
	bool allowedPosition(pair<int, int>);
	bool checkConnectedMap();

	//checker
	bool Map::isSpace(pair<int, int> position);
	bool Map::isBlock(pair<int, int> position);
	bool Map::isArtifact(pair<int, int> position);
	bool Map::isMonster(pair<int, int> position);
	bool Map::isEndPort(pair<int, int> position);


	
};


