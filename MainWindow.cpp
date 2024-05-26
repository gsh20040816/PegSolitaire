#include<iostream>
#include<Windows.h>
#include"ChessBoard.h"
#include<graphics.h>
#include<conio.h>
using namespace std;
const int width = 600, height = 800;

void startGame()
{
	chessBoard board(1, width, height);
	board.printBoard();
	while (1)
	{
		auto move = board.getMouseMove();
		int startX = move.first.first, startY = move.first.second;
		int endX = move.second.first, endY = move.second.second;
		if (board.moveChess(startX, startY, endX, endY))
		{
			cleardevice();
			board.printBoard();
		}
	}
}

void initBoard()
{
	const color_t backColor = BLUE;
	initgraph(width, height);
	setbkcolor(backColor);
}