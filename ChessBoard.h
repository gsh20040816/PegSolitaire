#pragma once

class chessBoard
{
private:
	//0:正方形棋盘 1:六边形棋盘
	//正方形棋盘使用二维数组存储
	//六边形棋盘使用偏移的二维数组存储
	int type;
	const static int size = 20;
	//0:空 1:非空 -1:不可达
	int board[size][size];

public:
	chessBoard(int type);
	~chessBoard();
	void printBoard();
	void moveChess(int startX, int startY, int endX, int endY);
};