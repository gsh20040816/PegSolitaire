#include"ChessBoard.h"
#include<iostream>
#include<fstream>
#include<string>
#include<graphics.h>
using namespace std;

chessBoard::chessBoard(int type, int width, int height)
{
	string filename = "Cases/" + to_string(type) + ".txt";
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "找不到数据文件，请检查文件是否存在" << endl;
		exit(0);
	}
	this->width = width;
	this->height = height;
	fin >> this->boardSize >> this->type;
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			board[i][j] = -1;
	for (int i = 0; i < this->boardSize; i++)
		for (int j = 0; j < this->boardSize; j++)
			fin >> board[i][j];
}

chessBoard::~chessBoard()
{
}

void chessBoard::printBoard()
{
	const int textX = width / 4, textY = (height - width) / 4;
	const int textWidth = width / 2, textHeight = (height - width) / 2;

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(textHeight / 3, 0, "黑体");
	outtextrect(textX, textY, textWidth, textHeight, "欢迎来到孔明棋");
	if (type == 0)
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				int x = width / boardSize * i + width / boardSize / 2;
				int y = height - width + width / boardSize * j + width / boardSize / 2;
				int r = width / boardSize / 3;
				if (board[i][j] != -1)
				{
					if (board[i][j] == 1)
						fillcircle(x, y, r);
					else
						circle(x, y, r);
				}
			}
		}
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
	if (type == 0)
	{
		int dis = abs(startX - endX) + abs(startY - endY);
		if (dis != 2)return -1;
		if (startX != endX && startY != endY)return -1;
		//0:左 1:上 2:右 3:下
		if (startX == endX)
		{
			if (startY > endY)
				return 0;
			else
				return 2;
		}
		else
		{
			if (startX > endX)
				return 1;
			else
				return 3;
		}
		return -1;
	}
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
			int x = width / boardSize * i + width / boardSize / 2;
			int y = height - width + width / boardSize * j + width / boardSize / 2;
			int r = width / boardSize / 3;
			if ((start.first - x) * (start.first - x) + (start.second - y) * (start.second - y) <= r * r)
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
			int x = width / boardSize * i + width / boardSize / 2;
			int y = height - width + width / boardSize * j + width / boardSize / 2;
			int r = width / boardSize / 3;
			if ((end.first - x) * (end.first - x) + (end.second - y) * (end.second - y) <= r * r)
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
	if (type == 0)
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if (board[i][j] == 0)
				{
					if (i > 0 && board[i - 1][j] == 1 && i > 1 && board[i - 2][j] == 1)
						return -1;
					if (i < boardSize - 1 && board[i + 1][j] == 1 && i < boardSize - 2 && board[i + 2][j] == 1)
						return -1;
					if (j > 0 && board[i][j - 1] == 1 && j > 1 && board[i][j - 2] == 1)
						return -1;
					if (j < boardSize - 1 && board[i][j + 1] == 1 && j < boardSize - 2 && board[i][j + 2] == 1)
						return -1;
				}
			}
		}
		return num;
	}
}

void chessBoard::gameWin()
{
	const int width0 = 400, height0 = 100;
	const color_t backColor = RED;
	setfont(height0 / 2, 0, "黑体");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextrect(0, 0, width0, height0, "恭喜你，你赢了！按空格返回初始界面");
}

void chessBoard::gameLose()
{
	const int width0 = 400, height0 = 100;
	const color_t backColor = RED;
	setfont(height0 / 2, 0, "黑体");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextrect(0, 0, width0, height0, "你输了！按空格返回初始界面");
}