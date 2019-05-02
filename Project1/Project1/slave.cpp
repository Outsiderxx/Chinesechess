#include "slave.h"

slave::slave(){}
slave::slave(int nowx, int nowy, int type)
{
	setx(nowx);
	sety(nowy);
	if (type == 7) //black
	{
		setCamp(false);
	}
	else if(type == 14) //red
	{
		setCamp(true);
	}
}
slave::~slave(){}
bool slave::isMovable(int dest_x, int dest_y, const int *board[])
{
	bool passRiverOrNot = false;
	int nowx = getx();
	int nowy = gety();

	if (dest_x == nowx && dest_y == nowy) //move to the original position.
	{
		//move again.
		return 0;
	}
	if (!getCamp())  // black
	{
		if (board[dest_x][dest_y] >= 1 && board[dest_x][dest_y] <= 7) { return 0; } // the same camp
		if (nowy >= 5) passRiverOrNot = true;
		if (dest_y < nowy) //slave cannot go back.
		{
			//move again.
			return 0;
		}
		if (!passRiverOrNot) //slave cannot go left or right before pass the river.
		{
			if (dest_x != nowx)
			{
				//move again.
				return 0;
			}
		}
		return 1;
	}
	else		// red
	{
		if (nowy <= 4) passRiverOrNot = true;
		if (board[dest_x][dest_y] >= 8 && board[dest_x][dest_y] <= 14) { return 0; } // the same camp
		if (dest_y > nowy) //slave cannot go back.
		{
			//move again.
			return 0;
		}
		if (!passRiverOrNot) //slave cannot go left or right before pass the river.
		{
			if (dest_x != nowx)
			{
				//move again.
				return 0;
			}
		}
		return 1;
	}
}