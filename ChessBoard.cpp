#include"ChessBoard.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

chessBoard::chessBoard(int type)
{
	string filename = "Cases/" + to_string(type) + ".txt";
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "找不到数据文件，请检查文件是否存在" << endl;
		exit(0);
	}
	int m;
	fin >> m >> this->type;
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			board[i][j] = -1;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			fin >> board[i][j];
}

chessBoard::~chessBoard()
{
}

void chessBoard::printBoard()
{
	if (type == 0)
	{
		for (int i = 0; i < size; i++)
		{
			bool flag = false;
			for (int j = 0; j < size; j++)
				if (board[i][j] != -1)
					flag = true;
			if (!flag)
				break;
			flag = false;
			for (int j = 0; j < size; j++)
			{
				if (board[i][j] != -1)
				{
					flag = true;
					if (board[i][j] == 1)
						cout << "■";
					else
						cout << "□";
				}
				else
				{
					if (flag)
						break;
					cout << " ";
				}
			}
			cout << endl;
		}
	}
}

bool chessBoard::moveChess(int startX, int startY, int endX, int endY)
{
	if (startX < 0 || startX >= size || startY < 0 || startY >= size)return false;
	if (endX < 0 || endX >= size || endY < 0 || endY >= size)return false;
	if (board[startX][startY] != 1 || board[endX][endY] != 1)return false;
	int direction = checkDirection(startX, startY, endX, endY);
	if (direction == -1)return false;
	auto nextPlace = getNextPlace(endX, endY, direction);
	int nextX = nextPlace.first, nextY = nextPlace.second;
	if (nextX < 0 || nextX >= size || nextY < 0 || nextY >= size)return false;
	if (board[nextX][nextY] != 0)return false;
	board[startX][startY] = 0;
	board[endX][endY] = 0;
	board[nextX][nextY] = 1;
	return true;
}

int chessBoard::checkDirection(int startX, int startY, int endX, int endY)
{
	if (type == 0)
	{
		int dis = abs(startX - endX) + abs(startY - endY);
		if (dis != 1)return -1;
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