#include <stdio.h>

#include "file.h"

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

void set_game(int (*box)[4], int *step, int *point)
{
	FILE *fp = fopen("game_file.bat", "r");

	for (int i = 0; i < 4 ; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			fscanf(fp, "%d", box[i] + j);
		}
	}

	fscanf(fp, "%d%d", step, point);

	fclose(fp);
}
