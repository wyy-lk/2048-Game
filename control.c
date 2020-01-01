#include <termios.h> 
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "control.h"

static char my_getch();

//用户的操作
int user_command()
{
	char ch;
	if ( (ch = my_getch())== '\n')   //如果是换行符
	{
		return QUIT;
	}
	//up - "\033[A"
	//down - "\033[B"
	//right - "\033[C"
	//left - "\033[D"
	//\033 = 0x1b = 27 = Esc 键 ， 也就是说up down left right 这些键，每个都由三个字符组成。
	//方向键控制上下左右
	else if (ch == 27)   //如果是按下了Esc键
	{
		if (my_getch() == 91)    //如果再次按下[键
		{
			switch(my_getch())  
			{
				case 65 : return UP;
				case 66 : return DOWN;
				case 67 : return RIGHT;
				case 68 : return LEFT;
				default : break;
			}
		}
	}
	//w s d a控制上下左右
	else
	{
		switch(ch)
		{
			case 'w': return UP;
			case 's': return DOWN;
			case 'd': return RIGHT;
			case 'a': return LEFT;
			case ':': 
				if((ch = my_getch()) == 'q')  //按下 :q 退出
				{
					return QUIT;
				}	 
				else if (ch == 's')   //按下 :s 保存当前进度
				{
					return SAVE;	
				}
				else if (ch == 'r')   //按下 :r 恢复上次保存的进度
				{
					return READ;	
				}
			default : break;
		}
	}
	//如果按下的是其他键也表示保存
	return SAVE;
}

//控制终端输入不在终端显示，而是会通过输入控制程序
char my_getch()
{
        int c = 0;  
	int res = 0;
        struct termios old_opts, new_opts;
        res = tcgetattr(STDIN_FILENO, &old_opts);   //获取原有属性，返回0表示成功，-1表示失败
        assert(res == 0);                           //如果出错，则终止程序，即条件res == 0 为假时

        memcpy(&new_opts, &old_opts, sizeof(new_opts));  //将原有属性拷贝给新的属性
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);  //修改新的属性
        res = tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);   //设置新的属性，返回0表示成功，-1表示失败，TCSANOW表示更改立即发生
	assert(res == 0);

        c=getchar();    //输入一个字符

        res = tcsetattr(STDIN_FILENO, TCSANOW, &old_opts);  //每次输入完一个字符后，又设置回原有的属性
        assert(res == 0);                         //如果出错，则终止程序
        return c;
}


