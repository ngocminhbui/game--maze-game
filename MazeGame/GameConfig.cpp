#include "GameConfig.h"

vector<pair<string, string>> GameConfig::_configTable;

//public functions

string GameConfig::getConfig(string configName){
	for (int i = 0; i < _configTable.size(); i++)
		if (_configTable[i].first == configName)
			return _configTable[i].second;
}


//private functions
GameConfig::GameConfig(string configFile){
	loadConfig(configFile);
}

void GameConfig::loadConfig(string configFile){
	ifstream in(configFile);
	string line;
	while (getline(in, line)){
		istringstream sstream(line);
		string configName;
		string configValue;
		getline(sstream, configName, ',');
		getline(sstream, configValue);
		_configTable.push_back(pair<string, string>(configName, configValue));
	}
}


void GameConfig::reConfig(string key, string newValue){
	for (int i = 0; i < _configTable.size(); i++)
		if (_configTable[i].first == key)
			_configTable[i].second = newValue;
}