#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "control.h"

static int merge_line(int *a);
static int up_move(int (*box)[4]);
static int down_move(int (*box)[4]);
static int left_move(int (*box)[4]);
static int right_move(int (*box)[4]);

int merge(int (*box)[4], int dir)
{
	int score = 0;
	int box_tmp[4][4];
	
	memcpy(box_tmp, box, 16 * sizeof(int));

	switch(dir)
	{
		case UP : score = up_move(box); break;
		case DOWN : score = down_move(box); break;
		case RIGHT : score = left_move(box); break;
		case LEFT : score = right_move(box); break;
		default : break;
	}

	if (memcmp(box_tmp, box, 16 * sizeof(int)) == 0)
	{
		return NOSCORE;
	}

	return score;
}

int check(int (*box)[4])
{
	int ret = LOSE;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (box[i][j] == 2048)
			{
				return WIN;
			}
			else if ((box[i][j] == 0) ||
				(j < 3 && box[i][j] == box[i][j + 1]) ||
				(j < 3 && box[j][i] == box[j + 1][i]))
			{
				ret = GAMING;
			}
		}
	}

	return ret;
}

int randnumber(int (*box)[4])
{
	int num = rand() % 5, cnt = 0, index;

	if (num < 4)
	{
		num = 2;
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (box[i][j] == 0)
			{
				++cnt;
			}
		}
	}
	

	index = rand() % cnt + 1;

	cnt = 0;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (box[i][j] == 0)
			{
				++cnt;

				if (index == cnt)
				{
					box[i][j] = num;
				}
			}
		}
	}

}

int merge_line(int *a)
{
	int score = 0;

	for (int i = 0; i < 3; ++i)
	{
		if (a[i] != 0 && a[i] == a[i + 1])
		{
			a[i] *= 2;
			score += a[i];
			a[i + 1] = 0;
			++i;
		}
		else if(i < 2 && a[i + 1] == 0 && a[i] == a[i + 2])
		{
			a[i] *= 2;
			score += a[i];
			a[i + 2] = 0;
			i += 2;	
		}
		else if(i == 0 && a[i + 1] == 0 && 
				a[i + 2] == 0 && a[i] == a[i + 3])
		{
			a[i] *= 2;
			score += a[i];
			a[i + 3] = 0;
			i += 3;	
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		int j = i;

		while (a[j] == 0 && j < 3)
		{
			++j;
		}

		if (j > i)
		{
			a[i] = a[j];
			a[j] = 0;
		}

	}

	return score;
}

int up_move(int (*box)[4])
{
	int score = 0, a[4];
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			a[j] = box[j][i];
		}
		score += merge_line(a);
		for (int j = 0; j < 4; ++j)
		{
			box[j][i] = a[j];
		}
	}

	return score;
}

int down_move(int (*box)[4])
{
	int score = 0, a[4];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			a[j] = box[4 - 1 - j][i];
		}

		score += merge_line(a);

		for (int j = 0; j < 4; ++j)
		{
			box[4 - 1 -j][i] = a[j];
		}
	}

	return score;
}

int right_move(int (*box)[4])
{
	int score = 0, a[4];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			a[j] = box[i][j];
		}

		score += merge_line(a);

		for (int j = 0; j < 4; ++j)
		{
			box[i][j] = a[j];
		}
	}

	return score;	
}

int left_move(int (*box)[4])
{
	int score = 0, a[4];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			a[j] = box[i][4 - 1 - j];
		}

		score += merge_line(a);

		for (int j = 0; j < 4; ++j)
		{
			box[i][4 - 1 - j] = a[j];
		}
	}

	return score;		
}
