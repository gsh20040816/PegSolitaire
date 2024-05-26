#pragma once
#include<iostream>
using std::pair;

class chessBoard
{
private:
	//0:正方形棋盘 1:六边形棋盘
	//正方形棋盘使用二维数组存储
	//六边形棋盘使用偏移的二维数组存储
	int type;
	const static int size = 20;
	int boardSize, width, height;
	//0:空 1:非空 -1:不可达
	int board[size][size];
	//检查方向是否合法，以及判断下一步是哪个方向
	//type:0
	//0:左 1:上 2:右 3:下
	//type:1
	//0:左 1:左上 2:右上 3:右 4:右下 5:左下
	int checkDirection(int startX, int startY, int endX, int endY);
	pair<int, int>getNextPlace(int startX, int startY, int direction);

public:
	chessBoard(int type, int width, int height);
	~chessBoard();
	void printBoard();//打印棋盘
	bool moveChess(int startX, int startY, int endX, int endY);//移动棋子并判断是否合法
	pair<pair<int, int>,pair<int,int>>getMouseMove();//获取鼠标移动棋子信息
	int gameEnd();//判断游戏是否结束，未结束返回-1，结束返回剩余棋子数
	void gameWin();
	void gameLose();
};