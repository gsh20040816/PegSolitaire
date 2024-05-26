#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>
#include"ChessBoard.h"
#include<graphics.h>
#include<conio.h>
using namespace std;
const int width = 600, height = 800;

void startRound(int roundID)
{
	chessBoard board(roundID, width, height);
	cleardevice();
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
		int num = board.gameEnd();
		if (num != -1)
		{
			cleardevice();
			if (num == 1)
				board.gameOver((char *)"你赢了！按空格返回初始界面");
			else
				board.gameOver((char *)"你输了！按空格返回初始界面");
			break;
		}
	}
	getch();
}

void initBoard()
{
	const color_t backColor = BLUE;
	initgraph(width, height);
	setbkcolor(backColor);
}

void startGame()
{
	while (1)
	{
		cleardevice();
		setfont(45, 0, "黑体");
		setcolor(WHITE);
		setbkcolor(BLUE);
		outtextxy(100, 200, "请按键选择");
		outtextxy(150, 300, "1.完整棋局");
		outtextxy(150, 400, "2.残局");
		outtextxy(150, 500, "3.退出");
		int choice = getch();
		while (choice != '1' && choice != '2' && choice != '3')
		{
			choice = getch();
		}
		if (choice == '3')break;
		else
		{
			string filename = "Rounds/" + to_string(choice-'0') + ".txt";
			
			ifstream fin;
			fin.open(filename);
			vector<pair<int, string>>rounds;
			int roundID = 0;
			string roundDesription;
			while (fin >> roundID >> roundDesription)
				rounds.push_back(make_pair(roundID, roundDesription));
			fin.close();
			//让用户选择关卡
			cleardevice();
			setfont(45, 0, "黑体");
			setcolor(WHITE);
			outtextxy(100, 100, "请按键选择");
			for (int i = 0; i < rounds.size(); i++)
			{
				char msg[100];
				sprintf_s(msg, 100, "%d0[%d].%s", choice, rounds[i].first % 100, rounds[i].second.c_str());
				outtextxy(150, 200 + i * 80, msg);
			}
			outtextxy(150, 200 + rounds.size() * 80, "7.返回上一级");
			int choice = getch();
			if (choice == '7')continue;
			while (choice<'1' || choice>rounds.size() + '0')
				choice = getch();
			startRound(rounds[choice - '0' - 1].first);
		}
	}
}