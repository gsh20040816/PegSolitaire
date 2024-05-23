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

void moveChess(int startX, int startY, int endX, int endY)
{

}