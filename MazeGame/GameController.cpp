#include "GameController.h"


//Singleton
GameController* GameController::_instance = NULL;

GameController* GameController::createInstance(string configFile){
	if (_instance == NULL)
		_instance = new GameController(configFile);
	return _instance;
}


//end singleton

GameController::GameController(string configFile){
	GameConfig::loadConfig(configFile);
}

GameController* GameController::getInstance(){
	return GameController::_instance;
}


int GameController::getCurrentYear(){
	return _year;
}

//gameflow control
bool GameController::run(){
	srand(time(NULL));
	GraphicFuntions::ClearConsole();
	//set gameturn, gameyear, create Notification, set console size
	setupBaseGame();

	//Create player and select config
	startGame();

	//setup game and create Map
	GraphicFuntions::ClearConsole();
	setupDisplay();

	//create Map
	Map::createInstance(Player::getInstance()->getLevel());
	
	//display map to screen
	displayMap();

	//on Game
	int loseWinFlag = onGame();
	if (loseWinFlag == WIN){
		ostringstream oss;
		oss << "You win, your point: " << Player::getInstance()->getScore(true);
		Notification::getInstance()->announce(oss.str());
	}

	else {
		Player::getInstance()->setScore(0);
		Notification::getInstance()->announce("You lose, your point: 0");
	}

	//register score
	highScore(loseWinFlag==WIN, true);

	//EndGame
	Player::getInstance()->showBackpack();

	return  endGame(loseWinFlag);
	
}

int GameController::onGame(){
	pair<int, int> originalPosition = Map::getInstance()->getStartPoint();

	vector<IMapMovingObject*> movingObjectList = Map::getInstance()->getMovingObject();

	do{
		//update utility
		Notification::getInstance()->updateTurnBox(Player::getInstance()->getTotalMove(), Player::getInstance()->getBaloWeight());
		vector<pair<int, int>> path = findPath(originalPosition, Map::getInstance()->getEndPoint());
		displayPath(path);

		Sleep(100);
		_year++;
		_gameTurn++;

		//main
		int nextMove = Player::getInstance()->nextMove();
		
		clearPath(path);
		
		pair<int, int> backMove = originalPosition;

		MovePlayer(nextMove, originalPosition);

		//MoveObject(originalPosition, movingObjectList);//smart Monster mode
		MoveObject(backMove, movingObjectList); //silly monster mode


		GraphicFuntions::Draw(DrawCommand(originalPosition, stoi(GameConfig::getConfig("archeologistColor")), 0, 'X'));

		if (Map::getInstance()->isMonster(originalPosition) == true){
			GraphicFuntions::Draw(DrawCommand(originalPosition, stoi(GameConfig::getConfig("archeologistColor")), stoi(GameConfig::getConfig("monsterColor")), 'X'));
			return LOSE;
		}
	} while (Map::getInstance()->getEndPoint() != originalPosition);

	

	if (Player::getInstance()->getNArtifact() == 0)
		return LOSE;
	else return WIN;
}

bool GameController::MoveObject(pair<int, int> humanPosition, vector<IMapMovingObject*> & movingObjectList){
	int n = movingObjectList.size();
	for (int i = 0; i < n; i++){
		pair<int, int> oldPos = movingObjectList[i]->getPosition();
		pair<int, int> newPos = movingObjectList[i]->updateState(humanPosition);

		if (newPos == oldPos) continue;
		if (newPos == Map::getInstance()->getEndPoint()) continue;
		if (Map::getInstance()->isSpace(newPos) == false) continue;


		movingObjectList[i]->setPosition(newPos);

		Map::getInstance()->setObject(movingObjectList[i], newPos);
		Map::getInstance()->setObject(NULL, oldPos);


		GraphicFuntions::Draw(DrawCommand(oldPos, 0, 0, ' '));
		GraphicFuntions::Draw(movingObjectList[i]->draw());

		if ((*Map::getInstance())(oldPos) != NULL){
			GraphicFuntions::Draw((*Map::getInstance())(oldPos)->draw());
		}
	}
	return true;
}

bool GameController::MovePlayer(const int Direction, pair<int, int> &origPos) {
	pair<int, int> startPos = origPos;
	switch (Direction) {
	case UP: {
		if (Map::getInstance()->allowedPosition(pair<int, int>(origPos.first, origPos.second - 1)) && Map::getInstance()->isBlock(pair<int, int>(origPos.first, origPos.second - 1)) == false) {
			
			GraphicFuntions::PlaceCursor(origPos.first, origPos.second);
			printf(" ");

			origPos.second -= 1;
		}
	} break;

	case DOWN: {
		if (Map::getInstance()->allowedPosition(pair<int, int>(origPos.first, origPos.second + 1)) && Map::getInstance()->isBlock(pair<int, int>(origPos.first, origPos.second + 1)) == false) {
			GraphicFuntions::PlaceCursor(origPos.first, origPos.second);
			printf(" ");

			origPos.second += 1;
		}
	} break;

	case LEFT: {
		if (Map::getInstance()->allowedPosition(pair<int, int>(origPos.first - 1, origPos.second)) && Map::getInstance()->isBlock(pair<int, int>(origPos.first - 1, origPos.second)) == false) {
			GraphicFuntions::PlaceCursor(origPos.first, origPos.second);
			printf(" ");

			origPos.first -= 1;
		}
	} break;

	case RIGHT: {
		if (Map::getInstance()->allowedPosition(pair<int, int>(origPos.first + 1, origPos.second)) && Map::getInstance()->isBlock(pair<int, int>(origPos.first + 1, origPos.second)) == false) {
			GraphicFuntions::PlaceCursor(origPos.first, origPos.second);
			printf(" ");

			origPos.first += 1;
		}
	} break;

	default: return false;
	}

	GraphicFuntions::Draw(DrawCommand(origPos, stoi(GameConfig::getConfig("archeologistColor")), 0, 'X'));


	if (Map::getInstance()->isArtifact(origPos) == true){
		bool canPush=Player::getInstance()->pushArtifact((*Map::getInstance())(origPos));
		if (canPush){
			Notification::getInstance()->announce("Picked " + ((IArtifact*)(Map::getInstance()->operator()(origPos)))->getInformation());
			(*Map::getInstance())(origPos) = NULL;
		}
		else
			Notification::getInstance()->announce("You can't pick this item,it's overweight");
	}

	if ((*Map::getInstance())(startPos) == NULL)
		GraphicFuntions::Draw(DrawCommand(startPos, 0, 0, ' '));
	else
		GraphicFuntions::Draw((*Map::getInstance())(startPos)->draw());

	return true;
}

void GameController::startGame(){
	GraphicFuntions::ClearConsole();
	string playerName;
	Notification::getInstance()->announce("Player's name?:");
	_flushall();
	getline(cin, playerName);
	


	GraphicFuntions::ClearConsole();

	Player::createPlayer(playerName);

	int choice = startGameMenu();
	switch (choice){
	case 1:break;
	case 2:reConfig(); break;
	case 3:exit(0); break;
	}
}

void GameController::reConfig(){
	char buffer[3];
	int x;
	Notification::getInstance()->announce("VK_COLOR of ARTIFACT, -1 to skip:");
	_flushall();
	cin >> x;
	if (x != -1)
		GameConfig::reConfig("artifactColor", Utils::intToString(x));

	Notification::getInstance()->announce("VK_COLOR of MONSTER, -1 to skip:");
	_flushall();
	cin >> x;
	if (x != -1)
		GameConfig::reConfig("monsterColor", Utils::intToString(x));

	Notification::getInstance()->announce("VK_COLOR of BLOCK, -1 to skip:");
	_flushall();
	cin >> x;
	if (x != -1)
		GameConfig::reConfig("blockColor", Utils::intToString(x));

	Notification::getInstance()->announce("VK_COLOR of ARCHEOLOGIST, -1 to skip:");
	_flushall();
	cin >> x;
	if (x != -1)
		GameConfig::reConfig("archeologistColor", Utils::intToString(x));
}

int GameController::startGameMenu(){
	Notification::getInstance()->announce("1. Start game");
	Notification::getInstance()->announce("2. Option");
	Notification::getInstance()->announce("3. Exit");
	Notification::getInstance()->announce("--Choice : ");
	int choice;
	_flushall();
	cin >> choice;
	return choice;
}

int GameController::endGameMenu(){
	Notification::getInstance()->announce("1. New game");
	Notification::getInstance()->announce("2. Quit game");
	Notification::getInstance()->announce("3. Top highscores");
	Notification::getInstance()->announce("4. Save map to file");
	Notification::getInstance()->announce("--Choice:");

	int choice;
	_flushall();
	cin >> choice;
	return choice;
}

bool GameController::endGame(bool loseWinFlag){
	
	int k;
	do{
		cin.sync();
		k = endGameMenu();
		if (k == 1)
			return true;
		else if (k == 2){
			return false;
		}
		else if (k == 3){
			highScore(loseWinFlag==WIN, false);
			return false;
		}
		else if (k == 4){
			saveMapToFile();
			return false;
		}
		else{
			Notification::getInstance()->announce("Lua chon sai");
			return false;
		}

	} while (k == 2);
}


void GameController::highScore(bool isWon, bool save){
	//Đọc dữ liệu từ file lưu điểm
	vector<pair<string, int>> scoreBoard;
	string highScoreLink = GameConfig::getConfig("highScoreFile");
	ifstream inFile(highScoreLink);
	string line;
	while (getline(inFile, line).good() == true){
		istringstream a(line);
		string name;
		int point;
		getline(a, name, ',');
		a >> point;
		scoreBoard.push_back(pair<string, int>(name, point));
	}
	inFile.close();

	if (save == false){
		//In ra thông báo top 5 người chơi cao điểm nhất
		Notification::getInstance()->announce("Top High Score:");
		for (int i = 0; i < scoreBoard.size(); i++){
			ostringstream ss;
			ss << scoreBoard[i].first << " ," << scoreBoard[i].second;
			Notification::getInstance()->announce(ss.str());
		}
		_flushall();
		char a;
		do{
			Notification::getInstance()->announce("an 1 de tiep tuc:");
			a = getchar();
		} while (a != '1');
	}
	if (save == true){
		//Thêm điểm của người chơi vào danh sách và cập nhật lại file

		scoreBoard.push_back(pair<string, int>(Player::getInstance()->getName(), Player::getInstance()->getScore(isWon)));
		for (int i = 0; i < scoreBoard.size()-1;i++)
			for (int j = i + 1; j < scoreBoard.size(); j++){

				if (scoreBoard[i].second < scoreBoard[j].second){
					pair<string, int> temp = scoreBoard[i];
					scoreBoard[i] = scoreBoard[j];
					scoreBoard[j] = temp;
				}
			}
		ofstream outFile(highScoreLink);

		int n = scoreBoard.size();
		if (n > 5) n = 5;
		for (int i = 0; i < n; i++)
			outFile << scoreBoard[i].first << "," << scoreBoard[i].second << endl;
		outFile.close();
	}

}


void GameController::saveMapToFile(){
	string mapFile = GameConfig::getConfig("saveMapFile");
	ofstream a(mapFile);

	vector<vector<char>> map = Map::getInstance()->getCharMap();

	pair<int, int> start = Map::getInstance()->getStartPoint();
	pair<int, int> end = Map::getInstance()->getEndPoint();

	map[start.first][start.second] = 'S';
	map[end.first][end.second] = 'F';

	int w = Map::getInstance()->getWidth();
	int h = Map::getInstance()->getHeight();

	for (int j = 0; j < h; j++){
		for (int i = 0; i < w; i++)
			a << map[i][j];
		a << endl;
	}

	
	
}

void GameController::setupBaseGame(){
	GameController::_gameTurn = 0;
	GameController::_year = stoi(GameConfig::getConfig("gameYear"));
	Notification::createInstance(pair<int, int>(stoi(GameConfig::getConfig("xNotification")), stoi(GameConfig::getConfig("yNotification"))), 
		pair<int, int>(stoi(GameConfig::getConfig("xTurnBox")), (stoi(GameConfig::getConfig("yTurnBox")))));
	GraphicFuntions::SetConsoleWindowSize(150, 150);
}

void GameController::setupDisplay(){
	IArtifact::setColor(stoi(GameConfig::getConfig("artifactColor")));
	IMonster::setColor(stoi(GameConfig::getConfig("monsterColor")));
	Block::setColor(stoi(GameConfig::getConfig("blockColor")));
}

void GameController::displayMap(){
	vector<vector<IMapObject*>> _map = Map::getInstance()->getMap();
	int width = Map::getInstance()->getWidth();
	int height = Map::getInstance()->getHeight();

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++){
			if (_map[i][j] == NULL)
				continue;
			else
				GraphicFuntions::Draw(_map[i][j]->draw());
		}

	pair<int, int> startPoint = Map::getInstance()->getStartPoint();
	pair<int, int> endPoint = Map::getInstance()->getEndPoint();

	GraphicFuntions::Draw(DrawCommand(endPoint, stoi(GameConfig::getConfig("archeologistColor")), stoi(GameConfig::getConfig("backgroundColor")), 'F'));
	GraphicFuntions::Draw(DrawCommand(startPoint, stoi(GameConfig::getConfig("archeologistColor")), stoi(GameConfig::getConfig("backgroundColor")), 'X'));
}

vector<pair<int, int>> GameController::findPath(pair<int, int> start, pair<int, int> end){
	Map* map = Map::getInstance();

	vector<pair<int, int>> path;
	vector<vector<int>> trace;
	vector<vector<bool>> mark;

	int w = map->getWidth();
	int h = map->getHeight();

	//Khởi tạo mảng truy vết
	trace.resize(w);
	for (int i = 0; i < w; i++)
		trace[i].resize(h, -1);

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
	s.push(start);
	mark[start.first][start.second] = true;

	bool isFound = false;
	pair<int, int> next;
	while (s.empty() == false && isFound == false){
		next = s.front();
		s.pop();

		if (next == end){
			isFound = true;
			break;
		}

		for (int i = 0; i < 4; i++){
			pair<int, int> con = pair<int, int>(next.first + dx[i], next.second + dy[i]);
			if (map->allowedPosition(con) == true && map->isBlock(con) == false && mark[con.first][con.second] == false){
				s.push(con);
				mark[con.first][con.second] = true;
				trace[con.first][con.second] = i;
			}
		}
	}

	if (isFound){
		pair<int, int> curr = next;
		do{
			int head = trace[curr.first][curr.second];
			head = (head + 2) % 4;
			curr = pair<int, int>(curr.first + dx[head], curr.second + dy[head]);
			if (curr == start)
				break;
			path.push_back(curr);
		} while (1);
	}
	return path;
}

void GameController::displayPath(vector<pair<int, int>> path){
	Map* map= Map::getInstance();
	int n = path.size();
	for (int i = 0; i < n; i++)
		if (map->isSpace(path[i]) == true)
			GraphicFuntions::Draw(DrawCommand(path[i], 15, 0, '.'));
}
void GameController::clearPath(vector <pair<int, int>> path){
	Map* map = Map::getInstance();
	int n = path.size();
	for (int i = 0; i < n; i++)
		if (map->isSpace(path[i]) == true)
			GraphicFuntions::Draw(DrawCommand(path[i], 0, 0, ' '));
}