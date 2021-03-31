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
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

char *g_string;

typedef struct s_token
{
	char			*command;
	char			**args;
	char			**flags;
	char			separate;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_term
{
	char			*termtype;
	char			*tgetnum;
	char			*termbuf;
	char			*tgetflag;
	char			*tgetstr;
	int				tgetent;
}					t_term;

typedef struct s_cursor
{
	int				start_pos;
	int				end_pos;
	int				current_pos;		
}					t_cursor;;

typedef struct s_flags
{
	int			single;
	int			twice;
}				t_flags;


typedef	struct s_all
{
	t_token			*token;
	t_term			term;
	t_cursor		cursor;
	t_flags			quote;
}					t_all;

void	terminal(t_all *all);
void	handle_sigint(int sig);
void	write_minishell(void);
void	ctrl_d_exit(void);
void	write_minishell(void);
int		ft_putchar(int c);
void	clear_buf(char **buf);
void	main_loop(t_all *all);
int		check_key(char *str, t_all *all);
int		check_key2(char *str, t_all *all);
void	parse_string(t_all *all);
void	delete_from_array(int i);
t_token	*create_new_token(t_token *token);
int		single_quote_start(int start);
int		double_quote_start(int start);
int		ecranisation(int start);
int		skip_space(int start);