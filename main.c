#include "main.h"

int main()
{
	srand(time(NULL));

	int points = 0;
	int step_points = 0;
	int steps = 0;
	int game_status = 0;
	int key;
	int box[][4] = {{0}, {0}, {0}, {0}};  //4*4地图
	
	//初始化一个二维数组的地图
	randnumber(box);
	//清屏
	clean_screen();
	//根据二维数组画出一个地图，此时game_status为0，是gaming状态
	draw_from(box, steps, points, game_status);

	//如果游戏胜利或失败，退出循环
	while ((game_status = check(box)) == GAMING)   //检查游戏的状态
	{
		//用户键入操作
		key = user_command();
		
		//如果用户在游戏进行中，有退出请求，也会退出循环
		if (key == QUIT)
		{
			break;
		}

		else if (key == SAVE)
		{
			//将当前的游戏状状态保存到一个文件中，其实就是将此时的二维数组和步数steps,分值points存进去
			save_game(box, steps, points);
			//draw_from(box, steps, points, game_status);
			continue;
		}
		else if (key == READ)
		{
			//从文件中读取上次保存的数据，注意参数是指针传递
			set_game(box, &steps, &points);
			//根据上次保存的数据，重新画出地图
			draw_from(box, steps, points, game_status);
			continue;
		}

		if ((step_points = merge(box, key)) != NOSCORE)  //获得每一步的分值
		{		
			points += step_points;
			randnumber(box);   //产生一个2或4放入地图中的空格中	
			draw_from(box, ++steps, points, game_status);  //画出新的地图
		}
	}
	
	//重新绘制游戏界面，表示是赢了，还是输了，或者是中途退出
	draw_from(box, steps, points, game_status);

	//结束游戏
	stop_draw();

	return 0;
}
