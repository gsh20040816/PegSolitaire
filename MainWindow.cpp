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
		if (startX == -2 && endX == -2)
		{
			if (board.undo())
			{
				cleardevice();
				board.printBoard();
			}
		}
		else if (startX == -3 && endX == -3)
		{
			cleardevice();
			board.gameOver((char*)"你退出了游戏！按空格返回初始界面");
			break;
		}
		else if (board.moveChess(startX, startY, endX, endY))
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
	setcaption("孔明棋");
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
		else if (choice == '1')
		{
			string filename = "Rounds/1.txt";
			ifstream fin;
			fin.open(filename);
			vector<pair<int, string>>rounds;
			int roundID = 0;
			string roundDesription;
			while (fin >> roundID >> roundDesription)
				rounds.push_back(make_pair(roundID, roundDesription));
			fin.close();
			cleardevice();
			setfont(45, 0, "黑体");
			setcolor(WHITE);
			outtextxy(100, 100, "请按键选择");
			for (int i = 0; i < rounds.size(); i++)
			{
				char msg[100];
				sprintf_s(msg, 100, "%c.%s", rounds[i].first % 100 < 10 ? rounds[i].first % 100 + '0' : rounds[i].first % 100 - 10 + 'a', rounds[i].second.c_str());
				outtextxy(150, 200 + i * 40, msg);
			}
			outtextxy(150, 200 + rounds.size() * 40, "e.返回上一级");
			int choice = getch();
			if (choice == 'e')continue;
			while ((choice < '1' || choice>'9') && (choice < 'a' || choice>'d'))
				choice = getch();
			startRound(rounds[choice >= '1' && choice <= '9' ? choice - '0' - 1 : choice - 'a' + 9].first);
		}
		else
		{
			string filename = "Rounds/2.txt";
			ifstream fin;
			fin.open(filename);
			vector<pair<int, string>>rounds;
			int roundID = 0;
			string roundDesription;
			while (fin >> roundID >> roundDesription)
				rounds.push_back(make_pair(roundID, roundDesription));
			fin.close();
			cleardevice();
			setfont(40, 0, "黑体");
			setcolor(WHITE);
			char msg[100];
			sprintf_s(msg, 100, "共有%d个残局", int(rounds.size()));
			outtextxy(100, 100, msg);
			outtextxy(100, 200, "请输入残局编号（三位数）");
			outtextxy(100, 300, "输入000返回上一级");
			int choice1 = getch();
			while (choice1 < '0' || choice1>'9')
				choice1 = getch();
			int choice2 = getch();
			while (choice2 < '0' || choice2>'9')
				choice2 = getch();
			int choice3 = getch();
			while (choice3 < '0' || choice3>'9')
				choice3 = getch();
			int choice = (choice1 - '0') * 100 + (choice2 - '0') * 10 + choice3 - '0';
			while (choice > rounds.size())
			{
				outtextxy(100, 400, "该残局不存在，请重新输入");
				choice1 = getch();
				while (choice1 < '0' || choice1>'9')
					choice1 = getch();
				choice2 = getch();
				while (choice2 < '0' || choice2>'9')
					choice2 = getch();
				choice3 = getch();
				while (choice3 < '0' || choice3>'9')
					choice3 = getch();
				choice = (choice1 - '0') * 100 + (choice2 - '0') * 10 + choice3 - '0';
			}
			if (choice == 0)continue;
			startRound(choice + 200);
		}
	}
}