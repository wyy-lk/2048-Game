#include "draw.h"
#include <stdio.h>

static void  dark_gray_block();
static void  light_gray_block();
static void  display1();
static void  display2();
static void  display_num(int a);

void draw_from(int box[][4], int steps, int points)
{
	printf("\033[1;37m\033[1;40m steps: %-8dpoints: %-10d\033[0m\n"
			, steps, points);
	display1();
	for (int i = 0; i < 4; ++i)
	{
		display2();
		light_gray_block();
		for (int j = 0; j < 4; ++j)
		{
			light_gray_block();
			display_num(box[i][j]);
			light_gray_block();
		}	
		light_gray_block();
		printf("\n");
		display2();
		display1();
	}
}

void draw_refresh(int box[][4], int steps, int points)
{
	printf("\33[?25l\33[18A");
	draw_from(box, ++steps, points);
}

void draw_win()
{
	printf(
	"\033[1;31m\033[1;40m\33[5m            You win :)            \033[0m\n");
}

void draw_lose()
{
	printf(
	"\033[1;31m\033[1;40m\33[5m            You lose :(           \033[0m\n");
}

void dark_gray_block()
{
	printf("\033[1;40m \033[0m");
}

void light_gray_block()
{
	printf("\033[1;47m \033[0m");
}

void display1()
{
	for (int i = 1; i <= 34; ++i)
	{
		light_gray_block();
	}
	printf("\n");
}

void display2()
{
	light_gray_block();
	for(int i = 1; i <= 4; ++i)
	{
		light_gray_block();
		for(int j = 1; j <= 6; ++j)
		{
			dark_gray_block();
		}
		light_gray_block();
	}
	light_gray_block();
	printf("\n");
}

void display_num(int a)
{
	switch (a)
	{
		case 0:
			printf("\033[1;40m      \033[0m"); break;
		case 2:
			printf("\033[0;37m\033[1;40m   2  \033[0m");break;
		case 4:
			printf("\033[0;32m\033[1;40m   4  \033[0m"); break;
		case 8:
			printf("\033[1;33m\033[1;40m   8  \033[0m"); break;
		case 16:
			printf("\033[1;34m\033[1;40m  16  \033[0m"); break;
		case 32:	
			printf("\033[1;31m\033[1;40m  32  \033[0m"); break;
		case 64:		
			printf("\033[0;36m\033[1;40m  64  \033[0m"); break;
		case 128: 
			printf("\033[0;37m\033[1;40m  128 \033[0m"); break;
		case 256:
			printf("\033[1;32m\033[1;40m  256 \033[0m"); break;
		case 512:	
			printf("\033[1;33m\033[1;40m  512 \033[0m"); break;	
		case 1024:
			printf("\033[1;34m\033[1;40m 1024 \033[0m"); break;
		case 2048:	
			printf("\033[1;36m\033[1;40m 2048 \033[0m"); break;
		default: break;
	}
	
}
