#ifndef MINISHELL_H
# define MINISHELL_H

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
#include <termios.h>

typedef struct s_token
{
	char			*str;
	int				type;
	char			**flags;
	char			separate;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_term
{
	char	*termtype;
	char	*tgetnum;
	char	*termbuf;
	char	*tgetflag;
	char	*tgetstr;
	int		tgetent;
}			t_term;

typedef	struct s_all
{
	t_token		token;
	t_term		term;
}				t_all;

#endif
