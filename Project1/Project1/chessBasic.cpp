#include "chessBasic.h"

bool chessBasic::getstatus()
{
	return status;
}

void chessBasic::setStatus(bool life) //0 = die 1 = life
{
	status = life;
}
void chessBasic::setx(int nowx)
{
	x = nowx;
}
void chessBasic::sety(int nowy)
{
	y = nowy;
}
int chessBasic::getx()
{
	return x;
}
int chessBasic::gety()
{
	return y;
}
