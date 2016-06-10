#pragma once
#include "Defs_Libs.h"

//singleton

class Notification{
private:
	static Notification* _instance;
	pair<int, int> _startTurnBox;
	pair<int, int> _startCursor;
	pair<int, int> _currentCursor;
	Notification(){};
	Notification(pair<int, int> notibox, pair<int, int> turnbox);
	~Notification(){
	}
public:
	static void  createInstance(pair<int, int> notibox, pair<int, int> turnbox);
	static void deleteInstance(){
		delete _instance;
	}
	static Notification* getInstance();
	void announce(string announcement);
	void updateTurnBox(int moves, int weight);
	void clearNotification();
};