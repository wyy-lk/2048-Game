#include <stdio.h>

#include "file.h"

//将游戏的状态存到文件中
void save_game(const int (*box)[4], int step, int point)
{
	FILE *fp = fopen("game_file.bat", "w");

	for (int i = 0; i < 4 ; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			fprintf(fp, "%d\n", box[i][j]);
		}
	}

	fprintf(fp, "%d\n%d\n", step, point);

	fclose(fp);
}

//将保存的游戏状态恢复到界面上
void set_game(int (*box)[4], int *step, int *point)
{
	FILE *fp = fopen("game_file.bat", "r");

	for (int i = 0; i < 4 ; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			fscanf(fp, "%d", box[i] + j);   ///box[i]+j 等同于 &box[i][j]
		}
	}

	fscanf(fp, "%d%d", step, point);

	fclose(fp);
}
