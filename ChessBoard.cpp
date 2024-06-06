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
	fin >> row >> col >> this->type;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = -1;
	undoX = width - (height - width) / 2;
	undoY = (height - width) / 2;
	undoR = (height - width) / 4;
	exitX = (height - width) / 2;
	exitY = (height - width) / 2;
	exitR = (height - width) / 4;
	numX = width / 2;
	numY = (height - width) / 2;
	numR = (height - width) / 4;
	preDirection = -1;
	preX = preY = -1;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col - (this->type == 1 && i % 2 == 0); j++)
			fin >> board[i][j];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col - (this->type == 1 && i % 2 == 0); j++)
		{
			int x = width / col * j + width / col / 2;
			int y = height - width + width / row * i + width / row / 2;
			if (this->type == 1 && i % 2 == 0)
				x += width / col / 2;
			posX[i][j] = x;
			posY[i][j] = y;
		}
	radius = width / max(row, col) / 3;
}

chessBoard::~chessBoard()
{
}

void chessBoard::printBoard()
{
	const int textX = width / 4, textY = (height - width) / 4;
	const int textWidth = width / 2, textHeight = (height - width) / 2;

	setfont(45, 0, "Consolas");
	setcolor(WHITE);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(undoX, undoY, "Undo");
	outtextxy(exitX, exitY, "Exit");
	outtextxy(numX, numY, to_string(getLeftNum()).c_str());
	settextjustify(LEFT_TEXT, LEFT_TEXT);
	circle(undoX, undoY, undoR);
	circle(exitX, exitY, exitR);
	circle(numX, numY, numR);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col - (type == 1 && i % 2 == 0); j++)
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
	if (startX < 0 || startX >= row || startY < 0 || startY >= col - (type == 1 && startX % 2 == 0))return false;
	if (endX < 0 || endX >= row || endY < 0 || endY >= col - (type == 1 && endX % 2 == 0))return false;
	if (board[startX][startY] != 1 || board[endX][endY] != 0)return false;
	int direction = checkDirection(startX, startY, endX, endY);
	if (direction == -1)return false;
	auto midPlace = getNextPlace(startX, startY, direction);
	int midX = midPlace.first, midY = midPlace.second;
	if (board[midX][midY] != 1)return false;
	board[startX][startY] = 0;
	board[midX][midY] = 0;
	board[endX][endY] = 1;
	preDirection = direction;
	preX = endX;
	preY = endY;
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
	while (!msg.is_up())
		msg = getmouse();
	pair<int, int>end = make_pair(msg.x, msg.y);
	int startX = -1, startY = -1, endX = -1, endY = -1;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col - (type == 1 && i % 2 == 0); j++)
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
	if ((start.first - undoX) * (start.first - undoX) + (start.second - undoY) * (start.second - undoY) <= undoR * undoR)
	{
		startX = -2, startY = -2;
	}
	if ((start.first - exitX) * (start.first - exitX) + (start.second - exitY) * (start.second - exitY) <= exitR * exitR)
	{
		startX = -3, startY = -3;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col - (type == 1 && i % 2 == 0); j++)
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
	if ((end.first - undoX) * (end.first - undoX) + (end.second - undoY) * (end.second - undoY) <= undoR * undoR)
	{
		endX = -2, endY = -2;
	}
	if ((end.first - exitX) * (end.first - exitX) + (end.second - exitY) * (end.second - exitY) <= exitR * exitR)
	{
		endX = -3, endY = -3;
	}
	return make_pair(make_pair(startX, startY), make_pair(endX, endY));
}

int chessBoard::getLeftNum()
{
	int num = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col - (type == 1 && i % 2 == 0); j++)
			if (board[i][j] == 1)
				num++;
	return num;
}

int chessBoard::gameEnd()
{
	int num = getLeftNum();
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col - (type == 1 && i % 2 == 0); j++)
			if (board[i][j] == 0)
				for (int direction = 0; direction < (type == 0 ? 4 : 6); direction++)
				{
					auto midPlace = getNextPlace(i, j, direction);
					int midX = midPlace.first, midY = midPlace.second;
					if (midX < 0 || midX >= row || midY < 0 || midY >= col - (type == 1 && midX % 2 == 0))continue;
					auto endPlace = getNextPlace(midX, midY, direction);
					int endX = endPlace.first, endY = endPlace.second;
					if (endX < 0 || endX >= row || endY < 0 || endY >= col - (type == 1 && endX % 2 == 0))continue;
					if (board[midX][midY] == 1 && board[endX][endY] == 1)
						return -1;
				}
	return num;
}

void chessBoard::gameOver(char* msg)
{
	const color_t backColor = GREEN;
	setbkcolor(backColor);
	setfont(30, 0, "Consolas");
	outtextxy(0, height/3, msg);
}

bool chessBoard::undo()
{
	if (preDirection == -1)return false;//没有上一步操作或已经悔过棋
	int direction = type == 0 ? (preDirection + 2) % 4 : (preDirection + 3) % 6;
	auto midPlace = getNextPlace(preX, preY, direction);
	int midX = midPlace.first, midY = midPlace.second;
	auto startPlace = getNextPlace(midX, midY, direction);
	int startX = startPlace.first, startY = startPlace.second;
	board[startX][startY] = 1;
	board[midX][midY] = 1;
	board[preX][preY] = 0;
	preDirection = -1;
	preX = preY = -1;
	return true;
}