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
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

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

typedef	struct s_shell
{
	t_list		*env;
}				t_shell;

int	ft_pwd();
void	get_save_env(t_list **head ,char **envp);
void	printf_env(t_list *head);
void	cd(t_list **head, char *arg);
char	*env_srh_edit(t_list **head, char *need, char *changes);
void	exec(char **argv, t_list *env, char *cmd);
char	**env_join(t_list *env);
char	*verify_dir(char *path, char *cmd);
void	free_array(char ***mas);

#endif
