#include"ChessBoard.h"
#include<iostream>
#include<fstream>
#include<string>
#include<graphics.h>
using namespace std;

chessBoard::chessBoard(int type, int width, int height)
{
	string filename = "Rounds/" + to_string(type) + ".txt";
	ifstream fin;
	fin.open(filename);
	this->width = width;
	this->height = height;
	fin >> this->boardSize >> this->type;
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			board[i][j] = -1;
	for (int i = 0; i < this->boardSize; i++)
		for (int j = 0; j < this->boardSize; j++)
			fin >> board[i][j];
	for (int i = 0; i < this->boardSize; i++)
	{
		for (int j = 0; j < this->boardSize; j++)
		{
			int x = width / (boardSize + 1) * j + width / (boardSize + 1) / 2;
			int y = height - width + width / boardSize * i + width / boardSize / 2;
			if (this->type == 1 && i % 2 == 0)
				x += width / (boardSize + 1) / 2;
			posX[i][j] = x;
			posY[i][j] = y;
		}
	}
	radius = width / boardSize / 3;
}

chessBoard::~chessBoard()
{
}

void chessBoard::printBoard()
{
	const int textX = width / 4, textY = (height - width) / 4;
	const int textWidth = width / 2, textHeight = (height - width) / 2;

	setfont(45, 0, "黑体");
	outtextxy(150, 50, "欢迎来到孔明棋");
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (board[i][j] != -1)
			{
				if (board[i][j] == 1)
					fillcircle(posX[i][j], posY[i][j], radius);
				else
					circle(posX[i][j], posY[i][j], radius);
			}
}

bool chessBoard::moveChess(int startX, int startY, int endX, int endY)
{
	if (startX < 0 || startX >= boardSize || startY < 0 || startY >= boardSize)return false;
	if (endX < 0 || endX >= boardSize || endY < 0 || endY >= boardSize)return false;
	if (board[startX][startY] != 1 || board[endX][endY] != 0)return false;
	int direction = checkDirection(startX, startY, endX, endY);
	if (direction == -1)return false;
	auto midPlace = getNextPlace(startX, startY, direction);
	int midX = midPlace.first, midY = midPlace.second;
	if (board[midX][midY] != 1)return false;
	board[startX][startY] = 0;
	board[midX][midY] = 0;
	board[endX][endY] = 1;
	return true;
}

int chessBoard::checkDirection(int startX, int startY, int endX, int endY)
{
	for (int direction = 0; direction < (type == 0 ? 4 : 6); direction++)
	{
		auto midPlace = getNextPlace(startX, startY, direction);
		int midX = midPlace.first, midY = midPlace.second;
		if (getNextPlace(midX, midY, direction) == make_pair(endX, endY))
			return direction;
	}
	return -1;
}

pair<int, int>chessBoard::getNextPlace(int startX, int startY, int direction)
{
	if (type == 0)
	{
		//0:左 1:上 2:右 3:下
		if (direction == 0)
			return make_pair(startX, startY - 1);
		if (direction == 1)
			return make_pair(startX - 1, startY);
		if (direction == 2)
			return make_pair(startX, startY + 1);
		if (direction == 3)
			return make_pair(startX + 1, startY);
		return make_pair(0, 0);
	}
	else
	{
		//0:左 1:左上 2:右上 3:右 4:右下 5:左下
		if (direction == 0)
			return make_pair(startX, startY - 1);
		if (direction == 1)
			return make_pair(startX - 1, startY - (startX & 1));
		if (direction == 2)
			return make_pair(startX - 1, startY + (startX + 1 & 1));
		if (direction == 3)
			return make_pair(startX, startY + 1);
		if (direction == 4)
			return make_pair(startX + 1, startY + (startX + 1 & 1));
		if (direction == 5)
			return make_pair(startX + 1, startY - (startX & 1));
	}
}

pair<pair<int, int>, pair<int, int>>chessBoard::getMouseMove()
{
	auto msg = getmouse();
	while (!msg.is_left() || !msg.is_down())
		msg = getmouse();
	pair<int, int>start = make_pair(msg.x, msg.y);
	while(!msg.is_up())
		msg = getmouse();
	pair<int, int>end = make_pair(msg.x, msg.y);
	int startX = -1, startY = -1, endX = -1, endY = -1;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if ((start.first - posX[i][j]) * (start.first - posX[i][j]) + (start.second - posY[i][j]) * (start.second - posY[i][j]) <= radius * radius)
			{
				startX = i;
				startY = j;
				break;
			}
		}
		if (startX != -1)break;
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if ((end.first - posX[i][j]) * (end.first - posX[i][j]) + (end.second - posY[i][j]) * (end.second - posY[i][j]) <= radius * radius)
			{
				endX = i;
				endY = j;
				break;
			}
		}
		if (endX != -1)break;
	}
	return make_pair(make_pair(startX, startY), make_pair(endX, endY));
}

int chessBoard::gameEnd()
{
	int num = 0;
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (board[i][j] == 1)
				num++;
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			if (board[i][j] == 0)
				for (int direction = 0; direction < (type == 0 ? 4 : 6); direction++)
				{
					auto midPlace = getNextPlace(i, j, direction);
					int midX = midPlace.first, midY = midPlace.second;
					if (midX < 0 || midX >= boardSize || midY < 0 || midY >= boardSize)continue;
					auto endPlace = getNextPlace(midX, midY, direction);
					int endX = endPlace.first, endY = endPlace.second;
					if (endX < 0 || endX >= boardSize || endY < 0 || endY >= boardSize)continue;
					if (board[midX][midY] == 1 && board[endX][endY] == 1)
						return -1;
				}
	return num;
}

void chessBoard::gameOver(char* msg)
{
	const color_t backColor = GREEN;
	setbkcolor(backColor);
	setfont(45, 0, "黑体");
	outtextxy(0, height/3, msg);
}