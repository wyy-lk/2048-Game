#include <stdlib.h>
#include "game.h"

static int merge_line(int a[]);
static int up_move(int box[][4]);
static int down_move(int box[][4]);
static int left_move(int box[][4]);
static int right_move(int box[][4]);
static int array_cpy(int a[][4], int b[][4]);
static int array_cmp(int a[][4], int b[][4]);

int merge(int box[][4], int dir)
{
	int score = 0;
	int box_tmp[4][4];
	array_cpy(box_tmp, box);

	switch(dir)
	{
		case 0 : 
			score = up_move(box); 
			break;
		case 1 : 
			score = down_move(box);
			break;
		case 2 :
			score = left_move(box);
			break;
		case 3 : 
			score = right_move(box);
			break;
		default : 
			break;
	}

	if (array_cmp(box_tmp, box) == 1)
	{
		return -1;
	}
	else 
	{
		return score;
	}

}

int check(int box[][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (box[i][j] == 2048)
			{
				return 1;
			}
		}
	}
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (box[i][j] == 0)
			{
				return 0;
			}
			else if (j < 3 && box[i][j] == box[i][j + 1])
			{
				return 0;
			}
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (box[j][i] == box[j + 1][i])
			{
				return 0;
			}
		}
	}

	return -1;
}

int randnumber(int box[][4])
{
	int num = rand() % 5;
	if (num < 4)
	{
		num = 2;
	}

	int cnt = 0;
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
	
	if (cnt)
	{
		int index = rand() % cnt + 1;
		cnt = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (box[i][j] == 0)
				{
					++cnt;
					if ( index == cnt)
					{
						box[i][j] = num;
					}
				}
			}
		}
	}
}


int merge_line(int a[])
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

int up_move(int box[][4])
{
	int score = 0;
	int a[4];
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

int down_move(int box[][4])
{
	int score = 0;
	int a[4];
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

int right_move(int box[][4])
{
	int score = 0;
	int a[4];
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

int left_move(int box[][4])
{
	int score = 0;
	int a[4];
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

int array_cpy(int a[][4], int b[][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			a[i][j] = b[i][j];
		}
	}
}

int array_cmp(int a[][4], int b[][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (a[i][j] != b[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}
