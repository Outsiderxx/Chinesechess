#include <fstream>
#include <conio.h>
#include "ChessBoard.h"

//初始化棋局和下棋方
ChessBoard::ChessBoard(vector<vector<int>> chessBoard,bool nowturn)
{
	curX = 0;
	curY = 0;
	curBoard.resize(10);
	for (int i = 0; i < 10; i++)
	{
		curBoard[i].resize(9);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			curBoard[i][j] = chessBoard[i][j];
		}
	}
	turn = nowturn;
}

//取得當前座標棋子種類
int ChessBoard::getChess(void)
{
	return curBoard[curY][curX];
}

//取得下棋方
bool ChessBoard::getTurn(void)
{
	return turn;
}

//改變下棋方
void ChessBoard::changeTurn(void)
{
	turn = 1 - turn;
}

//取得當前游標X座標
int ChessBoard::getCurX(void)
{
	return curX;
}

//取得當前游標Y座標
int ChessBoard::getCurY(void)
{
	return curY;
}

//移動游標位置
void ChessBoard::changeCoordinate(void)
{
	int direction = getch();
	switch (direction)
	{
	//UP
	case 72:
		if (curY > 0)
			curY--;
		break;
	//DOWN
	case 80:
		if (curY < 9)
			curY++;
		break;
	//LEFT
	case 75:
		if (curX > 0)
			curX--;
		break;
	//RIGHT
	case 77:
		if (curX < 8)
			curX++;
		break;
	default:
		break;
	}
}

//顯示菜單
//toDo=0 繼續 toDo=1 存檔 toDo=2 投降 toDo=3 說明 toDo=4 悔棋 toDo=5 離開遊戲 
int ChessBoard::menu(void)
{    
	int toDo = 0;
	//ESC清單畫面
	while (true)
	{
		if (kbhit())
		{
			int input = getch();
			if (input == 224)
			{
				input = getch();
				if (input == 72)
				{
					if (input == 0)
						toDo = 0;
					else
						toDo--;
				}
				else if (input == 80)
				{
					if (toDo == 5)
						toDo = 5;
					else
						toDo++;
				}
			}
			else if(input == 13)
			{
				switch (toDo)
				{
				case 0:
					return 0;
				case 1:
					saveFile();
					break;
				case 2:
					return 1;
				case 3:
					return 2;
				case 4:
					regret();
					return 0;
				case 5:
					saveFile();
					return 3;
				}
			}
		}
	}
}

//移動棋子
int ChessBoard::move(chessBasic* curChess)
{
	int returnValue;
	if (getChess() == 1)
		returnValue = 1;
	else if(getChess() == 8)
		returnValue = 2;
	else
		returnValue = 0;
	curBoard[curY][curX] = curBoard[curChess->gety()][curChess->getx()];
	curBoard[curChess->gety()][curChess->getx()] = 0;
	curChess->setx(curX);
	curChess->sety(curY);
	return returnValue;
}

//儲存棋局
void ChessBoard::saveBoard(void)
{
	preBoard.push_back(curBoard);
}

//悔棋
void ChessBoard::regret(void)
{
	if (preBoard.size() > 2)
	{
		curBoard = preBoard[preBoard.size() - 2];
		preBoard.pop_back();
		preBoard.pop_back();
	}
	else
	{
		cout << "無法悔棋" << endl;
	}
}

//存檔
void ChessBoard::saveFile(void)
{
	ofstream output("oldBoard.txt",ios::app);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			output << curBoard[i][j] << " ";
		}
		output << endl;
	}
	output << turn << endl;
}

vector<vector<int>> ChessBoard::getBoard(void)
{
	return curBoard;
}

void ChessBoard::printBoard(void)
{
	system("cls");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			switch (curBoard[i][j])
			{
			case 1:
				cout << "將 ";
				break;
			case 2:
				cout << "士 ";
				break;
			case 3:
				cout << "象 ";
				break;
			case 4:
				cout << "車 ";
				break;
			case 5:
				cout << "馬 ";
				break;
			case 6:
				cout << "包 ";
				break;
			case 7:
				cout << "卒 ";
				break;
			case 8:
				cout << "帥 ";
				break;
			case 9:
				cout << "仕 ";
				break;
			case 10:
				cout << "相 ";
				break;
			case 11:
				cout << "車 ";
				break;
			case 12:
				cout << "馬 ";
				break;
			case 13:
				cout << "炮 ";
				break;
			case 14:
				cout << "兵 ";
				break;
			default:
				cout << "空 ";
				break;
			}
		}
		cout << endl << endl;
	}
	if (turn)
		cout << "紅方下棋" << endl;
	else
		cout << "黑方下棋" << endl;
}

void ChessBoard::replay(void)
{
	curBoard = preBoard[0];
	printBoard();
	int index = 1;
	while (true)
	{
		if (index == preBoard.size())
		{
			system("pause");
			break;
		}
		if (kbhit())
		{
			int input = getch();
			if (input == 13)
			{
				curBoard = preBoard[index];
				printBoard();
				index++;
			}
		}
	}
}

void ChessBoard::win(bool whoWin)
{
	system("cls");
	if (whoWin)
		cout << "紅方勝" << endl;
	else
		cout << "黑方勝" << endl;
	bool replayFlag = 1;
	while (true)
	{
		if (kbhit())
		{
			int input = getch();
			if (input == 224)
			{
				input = getch();
				replayFlag = 1 - replayFlag;
			}
			else if (input == 13)
			{
				if (replayFlag)
					replay();
				break;
			}
		}
	}
}

bool ChessBoard::kingMeetKing(vector<vector<int>> board)	//king meet king
{
	int kingX1, kingX2, kingY1,kingY2;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 1)
			{
				kingY1 = i;
				kingX1 = j;
			}
			if (board[i][j] == 8)
			{
				kingY2 = i;
				kingX2 = j;
			}
		}
	}
	if (kingX1 == kingX2)
	{
		for (int loop=kingY1+1;loop<kingY2;loop++)
		{

			if (board[loop][kingX1] != 0)
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}