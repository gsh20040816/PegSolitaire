#include<iostream>
#include<Windows.h>
#include"ChessBoard.h"
//#include<graphics.h>
#include<conio.h>
using namespace std;

void startGame()
{
	/*initgraph(800, 800);

	setbkcolor(GREEN);

	getch();


	circle(200, 400, 30);
	fillcircle(100, 100, 40);

	roundrect(100, 100, 200, 200, 20, 20);
	getch();

	closegraph();*/

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