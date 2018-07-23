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
				case 65 : return 0;
				case 66 : return 1;
				case 67 : return 2;
				case 68 : return 3;
				default : break;
			}
		}
	}
	else
	{
		switch(ch)
		{
			case 'w': return 0;
			case 's': return 1;
			case 'd': return 2;
			case 'a': return 3;
			default : break;
		}
	}
	
	return 5;
}

char my_getch()
{
        int c=0;  int res=0;
        struct termios org_opts, new_opts;
        res=tcgetattr(STDIN_FILENO, &org_opts);
        assert(res==0);
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | 
							  ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();//
        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
        assert(res==0);
        return c;
}


