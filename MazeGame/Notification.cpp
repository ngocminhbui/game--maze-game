#include "Notification.h"
Notification* Notification::_instance;

Notification::Notification(pair<int, int> notibox, pair<int,int> turnbox){
	_startTurnBox = turnbox;
	_startCursor = notibox;
	_currentCursor = _startCursor;
}


void  Notification::createInstance(pair<int, int> notibox, pair<int, int> turnbox){
	_instance = new Notification(notibox,turnbox);
}

Notification* Notification::getInstance(){
	return _instance;
}

void Notification::announce(string announcement){
	//if (_currentCursor.second - _startCursor.second > 3)
	//clearNotification();
	GraphicFuntions::SetColor(10, 0);
	GraphicFuntions::PlaceCursor(_currentCursor.first, _currentCursor.second);
	cout << announcement;
	_currentCursor.first = _startCursor.first;
	_currentCursor.second++;
}

void Notification::clearNotification(){
	for (int j = _startCursor.second; j < _currentCursor.second; j++){
		for (int i = _startCursor.first; i <_startCursor.first + 60; i++){
			GraphicFuntions::PlaceCursor(i, j);
			GraphicFuntions::SetColor(0, 0);
			printf(" ");
		}
	}
	_currentCursor = _startCursor;
}

void Notification::updateTurnBox(int moves, int weight){
	GraphicFuntions::SetColor(10, 0);
	GraphicFuntions::PlaceCursor(_startTurnBox.first, _startTurnBox.second);
	printf("                                            ");
	GraphicFuntions::PlaceCursor(_startTurnBox.first, _startTurnBox.second+1);
	printf("                                            ");

	GraphicFuntions::PlaceCursor(_startTurnBox.first, _startTurnBox.second);
	cout << "Total moves:" << moves;

	GraphicFuntions::PlaceCursor(_startTurnBox.first, _startTurnBox.second+1);
	cout << "Total weight:" << weight;
}