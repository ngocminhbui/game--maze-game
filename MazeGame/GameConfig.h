#pragma once
#include "Defs_Libs.h"

class GameConfig{
private:
	static vector<pair<string, string>> _configTable;

	//Prevent default constructor
	GameConfig(){}
	GameConfig(string configFile);
protected:
public:
	static void loadConfig(string configFile);
	static string getConfig(string configName);
	static void reConfig(string key, string newValue);
};

