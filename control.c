#include <termios.h> 
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "control.h"

static char my_getch();

int user_command()
{
	char ch;
	if ( (ch = my_getch())== '\n')
	{
		return 4;
	}
	else if (ch == 27)
	{
		if (my_getch() == 91)
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
	else
	{
		switch(ch)
		{
			case 'w': return UP;
			case 's': return DOWN;
			case 'd': return RIGHT;
			case 'a': return LEFT;
			case ':': 
				if((ch = my_getch()) == 'q')
				{
					return QUIT;
				}	
				else if (ch == 's')
				{
					return SAVE;	
				}
				else if (ch == 'r')
				{
					return READ;	
				}
			default : break;
		}
	}
	
	return 5;
}

char my_getch()
{
        int c = 0;  
		int res = 0;
        struct termios org_opts, new_opts;
        res = tcgetattr(STDIN_FILENO, &org_opts);
        assert(res == 0);
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | 
							  ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();
        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
        assert(res == 0);
        return c;
}


