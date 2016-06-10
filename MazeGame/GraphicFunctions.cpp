#include "Defs_Libs.h"

void GraphicFuntions::RemoveCursor() {

	/* Remove the cursor (does not work in full screen) */
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;
	CursoInfo.dwSize = 1;         /* The size of caret */
	CursoInfo.bVisible = false;   /* Caret is visible? */
	SetConsoleCursorInfo(hConsole, &CursoInfo);

	return;
}

pair<int,int> GraphicFuntions::GetCursorPosition(){
	POINT point;
	GetCursorPos(&point);
	return pair<int, int>(point.x, point.y);
}

void GraphicFuntions::SetColor(const int foreground, const int background) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foreground | background);

	return;
}

void GraphicFuntions::PlaceCursor(const int x, const int y) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD PlaceCursorHere;
	PlaceCursorHere.X = x;
	PlaceCursorHere.Y = y;

	SetConsoleCursorPosition(hConsole, PlaceCursorHere);
	return;
}

void GraphicFuntions::ClearConsole(){
	system("cls");
}

void GraphicFuntions::Draw(DrawCommand a){
	PlaceCursor(a.position.first, a.position.second);
	SetColor(a.foreGround, a.backGround);
	printf("%c", a.character);
}


void GraphicFuntions::SetConsoleWindowSize(unsigned width, unsigned height) {
	HANDLE hConOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT r;
	COORD      c;
	hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConOut, c);

	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConOut, TRUE, &r);
}


void GraphicFuntions::flushInput(){
	HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(inputHandle);
}