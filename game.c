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
	//字节拷贝函数，将box中的数据拷贝到box_tmp中
	memcpy(box_tmp, box, 16 * sizeof(int)); 
	switch(dir)
	{
		case UP : score = up_move(box); break;
		case DOWN : score = down_move(box); break;
		case RIGHT : score = right_move(box); break;
		case LEFT : score = left_move(box); break;
		default : break;
	}
	
	//将这两个数组比较，如果相等，就表明按键不是上下左右，没有对游戏地图的状态产生变化
	if (memcmp(box_tmp, box, 16 * sizeof(int)) == 0)
	{
		return NOSCORE;
	}

	return score;
}

//查看游戏的状态
int check(int (*box)[4])
{
	int ret = LOSE;

	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//如果有某个格子的值已经为2048,则游戏胜利
			if (box[i][j] == 2048)
			{
				return WIN;
			}
			//如果有空格 或者 有相邻两个格子的值相同
			//则游戏还在进行中	
			else if ((box[i][j] == 0) ||
				(j < 3 && box[i][j] == box[i][j + 1]) ||
				(j < 3 && box[j][i] == box[j + 1][i]))
			{
				ret = GAMING;
			}
		}
	}
	//否则，既没有空格，也没有相邻两个数相同，更没有某个数值为2048
	//则游戏失败
	return ret;
}

//初始化
void randnumber(int (*box)[4])
{
	//产生一个随机数 在0-4之间
	int num = rand() % 5, cnt = 0, index;  

	//如果这个数小于4,就让它变成2
	//这个数是每次按下方向后产生的一个随机数
	if (num < 4)
	{
		num = 2;
	}

	//看有多少个为空的格子
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
	
	//产生一个1到cnt的随机数
	index = rand() % cnt + 1;

	cnt = 0;
	
	//将产生的随机数num放入随机放入某个空格中
	//如果某个格子是空的，且index等于cnt，就在这个格子放入随机数num
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (box[i][j] == 0)
			{
				++cnt;  //每遇到一个空格就计数

				if (index == cnt)
				{
					box[i][j] = num;
				}
			}
		}
	}

}

//合并一个方向上的所有数
int merge_line(int *a)
{
	int score = 0;
	
	for (int i = 0; i < 3; ++i)
	{
		//如果相邻两个数相同
		if (a[i] != 0 && a[i] == a[i + 1])
		{
			a[i] *= 2;
			score += a[i];
			a[i + 1] = 0;
			++i;
		}
		//如果是隔了一个数的两个数相同，且中间隔的那个数为0
		else if(i < 2 && a[i + 1] == 0 && a[i] == a[i + 2])
		{
			a[i] *= 2;
			score += a[i];
			a[i + 2] = 0;
			i += 2;	
		}
		//如果是第一个数和第四个数相同，且中间隔的那两个数为0
		else if(i == 0 && a[i + 1] == 0 && 
				a[i + 2] == 0 && a[i] == a[i + 3])
		{
			a[i] *= 2;
			score += a[i];
			a[i + 3] = 0;
			i += 3;	
		}
	}
	
	//再将每个数放到正确位置
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
	//此时i表示列，j表示行
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

	//此时i表示列，j表示行
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

int left_move(int (*box)[4])
{
	int score = 0, a[4];
	//此时i表示行，j表示列
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

int right_move(int (*box)[4])
{
	int score = 0, a[4];
	//此时i表示行，j表示列
	for(int i = 0; i < 4; ++i)
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
