#pragma once

#include <iostream>
using namespace std;

struct DrawCommand{
	pair<int, int> position;
	int foreGround;
	int backGround;
	char character;

	DrawCommand(pair<int, int> pos, int fore, int back, char charac){
		position = pos;
		foreGround = fore;
		backGround = back;
		character = charac;
	}
};

class GraphicFuntions{
private:
public:
	static pair<int, int> GetCursorPosition();
	static void RemoveCursor();

	static void SetColor(const int foreground, const int background);

	static void PlaceCursor(const int x, const int y);

	static void Draw(DrawCommand a);

	static void SetConsoleWindowSize(unsigned width, unsigned height);

	static void ClearConsole();

	static void flushInput();
};