#include "draw.h"
#include <stdio.h>

static void  dark_gray_block();
static void  light_gray_block();
static void  display1();
static void  display2();
static void  display3();
static void  display_num(int a);
static void  display_block(int a);

void draw_from(int box[][4], int steps, int points)
{
	printf("\n");
	display3();
	printf("    ");
	printf("\033[1;37m\033[1;40m points: %-12dsteps: %-6d\033[0m\n"
			, points, steps);
	display3();
	display1();
	for (int i = 0; i < 4; ++i)
	{
		printf("    ");
		light_gray_block();
		for (int j = 0; j < 4; ++j)
		{
			light_gray_block();
			display_block(box[i][j]);
			light_gray_block();
		}
		light_gray_block();
		printf("\n");

		printf("    ");
		light_gray_block();
		for (int j = 0; j < 4; ++j)
		{
			light_gray_block();
			display_num(box[i][j]);
			light_gray_block();
		}	
		light_gray_block();
		printf("\n");

		printf("    ");
		light_gray_block();
		for (int j = 0; j < 4; ++j)
		{
			light_gray_block();
			display_block(box[i][j]);
			light_gray_block();
		}
		light_gray_block();
		printf("\n");

		display1();
	}	
	display3();
	printf("    ");
	printf("\033[1;37m\033[1;40m         Try to get 2048!         \033[0m\n"		  );
	display3();
}

void draw_refresh(int box[][4], int steps, int points)
{
	printf("\33[?25l\33[24A");
	draw_from(box, ++steps, points);
}

void draw_win()
{
	printf("    ");
	printf("\33[?25l\33[2A");
	printf(
	"\033[1;31m\033[1;40m\33[5m            You win :)            \033[0m\n"
	);
	display3();
}

void draw_lose()
{
	printf("    ");
	printf("\33[?25l\33[2A");
	printf(
	"\033[1;31m\033[1;40m\33[5m            You lose :(           \033[0m\n"
	);
	display3();
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
	printf("    ");
	for (int i = 1; i <= 34; ++i)
	{
		light_gray_block();
	}
	printf("\n");
}

void display2()
{
	printf("    ");
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

void display3()
{
	printf("    ");
	for (int i = 1; i <= 34; ++i)
	{
		dark_gray_block();
	}
	printf("\n");
}

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
