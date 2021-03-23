#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../include/libft.h"
#include "../include/get_next_line.h"
#include <signal.h>
#include <term.h>
#include <curses.h>
#include <termcap.h>

typedef struct s_term
{
	char	*termtype;
	char	*tgetnum;
	char	termbuf[1024];
	char	*tgetflag;
	char	*tgetstr;
	int		tgetent;
}			t_term;