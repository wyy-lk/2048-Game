#include <stdio.h>
#include "draw.h"
#include "game.h"

#define draw_dark_line() printf("\t\033[1;40m%34s\033[0m\n","")
#define draw_light_line() printf("\t\033[1;47m%34s\033[0m\n","")
#define draw_light_block() printf("\033[1;47m  \033[0m");
#define back_to_first_line() printf("\33[?25l\033[27A")

static void print_step_and_point(int step, int point);
static void draw_2048(const int (*box)[4]);	
static void draw_info(int state);	
static void display_num(int a);
static void display_block(int a);

//画出整个游戏的界面
void draw_from (const int (*box)[4], int step, int point, int state)
{
	//显示游戏标题，步数，分数
	print_step_and_point(step, point);
	//显示游戏画面
	draw_2048(box);	
	//显示游戏状态 胜利 失败 游戏中
	draw_info(state);
	//在最后再添上一行黑色背景行
	back_to_first_line();
}

//清屏
void clean_screen()
{
	printf("\033[2J");   //清屏
}

//停止画面的显示
void stop_draw()	
{
	printf("\33[?25l\33[27B");
}

//显示游戏标题，步数，分数
void print_step_and_point(int step, int point)
{				
	printf("\t\033[1;40m%34s\033[0m\n","  __   __        __  ");
	printf("\t\033[1;40m%34s\033[0m\n","  __| |  | |__| |__| ");
	printf("\t\033[1;40m%34s\033[0m\n"," |__  |__|    | |__| ");
	printf("\t\033[1;40m  Points: %-24d""\033[0m\n"			
		"\t\033[1;40m  Steps: %-25d\033[0m\n", point, step);	
	draw_dark_line(); 
} 

//显示游戏画面
void draw_2048(const int (*box)[4])
{			
	draw_light_line(); 
	for (int i = 0; i < 4; ++i)
	{
		//第一行
		printf("\t");
		for (int j = 0; j < 4; ++j)
		{
			draw_light_block();	
			display_block(box[i][j]);
		}
		draw_light_block();
		
		//第二行 填数字
		printf("\n\t");;
		for (int j = 0; j < 4; ++j)
		{
			draw_light_block();
			display_num(box[i][j]);
		}
		draw_light_block();
		
		//第三行
		printf("\n\t");
		for (int j = 0; j < 4; ++j)
		{
			draw_light_block();
			display_block(box[i][j]);
		}
		draw_light_block();

		//第四行
		printf("\n");
		draw_light_line();
	}

}

//显示游戏状态 胜利 失败 游戏中
void draw_info(int state)
{
	draw_dark_line();		

	if (state == GAMING)		
	{
		printf("\t\033[1;40m%2sControl with WASD or Direction"
			"%2s\033[0m\n", "", "");
		printf("\t\033[1;40m%3s:q quit,  :s save,"
			"  :r read %3s\033[0m\n", "", "");
	}
	else if (state == WIN)
	{
		printf("\t\033[1;40m%9sCongratulations!%9s\033[0m\n", "", "");
		printf("\t\033[0;32m\33[1;40m%13sYOU WIN!%13s\033[0m\n", "", "");
	}
	else if (state == LOSE)	
	{
		printf("\t\033[1;40m%13sSorry...%13s\033[0m\n", "", "");
		printf("\t\033[0;31m\33[1;40m%13sYOU LOSE%13s\033[0m\n", "", "");
	}

	draw_dark_line();
}

//显示数字
void display_num(int a)
{
	switch (a)
	{
		case 0:
			printf("\033[1;40m      \033[0m"); break;
		case 2:
			printf("\033[0;43m\033[1;37m   2  \033[0m");break;
		case 4:
			printf("\033[0;44m\033[1;37m   4  \033[0m"); break;
		case 8:
			printf("\033[1;45m\033[1;37m   8  \033[0m"); break;
		case 16:
			printf("\033[1;42m\033[1;37m  16  \033[0m"); break;
		case 32:	
			printf("\033[1;41m\033[1;37m  32  \033[0m"); break;
		case 64:		
			printf("\033[0;46m\033[1;37m  64  \033[0m"); break;
		case 128: 
			printf("\033[0;43m\033[1;37m  128 \033[0m"); break;
		case 256:
			printf("\033[1;44m\033[1;37m  256 \033[0m"); break;
		case 512:	
			printf("\033[1;45m\033[1;37m  512 \033[0m"); break;	
		case 1024:
			printf("\033[1;46m\033[1;37m 1024 \033[0m"); break;
		case 2048:	
			printf("\033[1;41m\033[1;37m 2048 \033[0m"); break;
		default: break;
	}
}


void display_block(int a)
{
	switch (a)
	{
		case 0:
			printf("\033[1;40m      \033[0m"); break;
		case 2:
			printf("\033[0;43m\033[1;37m      \033[0m");break;
		case 4:
			printf("\033[0;44m\033[1;37m      \033[0m"); break;
		case 8:
			printf("\033[1;45m\033[1;37m      \033[0m"); break;
		case 16:
			printf("\033[1;42m\033[1;37m      \033[0m"); break;
		case 32:	
			printf("\033[1;41m\033[1;37m      \033[0m"); break;
		case 64:		
			printf("\033[0;46m\033[1;37m      \033[0m"); break;
		case 128: 
			printf("\033[0;43m\033[1;37m      \033[0m"); break;
		case 256:
			printf("\033[1;44m\033[1;37m      \033[0m"); break;
		case 512:	
			printf("\033[1;45m\033[1;37m      \033[0m"); break;	
		case 1024:
			printf("\033[1;46m\033[1;37m      \033[0m"); break;
		case 2048:	
			printf("\033[1;41m\033[1;37m      \033[0m"); break;
		default: break;
	}
	
}
