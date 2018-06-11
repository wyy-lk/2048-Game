#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "draw.h"
#include "control.h"
#include "game.h"

int main()
{
	srand(time(NULL));

	int points = 0;
	int step_points = 0;
	int steps = 0;
	int game_status = 0;
	int key;
	int box[][4] = {{0}, {0}, {0}, {0}};
	
	randnumber(box);
	
	draw_from(box, steps, points);

	while ((game_status = check(box)) == 0)
	{
		key = user_command();
		if ((step_points = merge(box, key)) != -1)
		{		
			points += step_points;
			randnumber(box);	
			draw_refresh(box, ++steps, points);
		}
	}

	draw_refresh(box, ++steps, points);
	
	if (game_status == 1)
	{
		draw_win();
	}
	else
	{
		draw_lose(steps, points);
	}

	return 0;
}
