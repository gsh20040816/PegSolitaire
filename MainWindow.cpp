#include<iostream>
#include<conio.h>
#include<Windows.h>
#include"ChessBoard.h"
using namespace std;

void startGame()
{
	chessBoard board(1);
	while (1)
	{
		system("cls");
		board.printBoard();
		cout << "请输入起始位置和目标位置" << endl;
		int startX, startY, endX, endY;
		cin >> startX >> startY >> endX >> endY;
		if (board.moveChess(startX, startY, endX, endY))
			cout << "成功" << endl;
		else
			cout << "失败" << endl;
	}
}