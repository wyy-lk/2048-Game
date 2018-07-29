#include "main.h"

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

	clean_screen();

	draw_from(box, steps, points, game_status);

	while ((game_status = check(box)) == GAMING)
	{
		key = user_command();

		if (key == QUIT)
		{
			break;
		}

		if ((step_points = merge(box, key)) != NOSCORE)
		{		
			points += step_points;
			randnumber(box);	
			draw_from(box, ++steps, points, game_status);
		}
	}

	draw_from(box, steps, points, game_status);

	stop_draw();

	return 0;
}
