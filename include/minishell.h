#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <termios.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
#include <sys/wait.h>

# define RESET			"\033[0m"
# define RED			"\033[1;31m"
# define LIGHT_GREEN	"\033[1;92m"
# define YELLOW			"\033[1;33m"
# define WHITE			"\033[1;37m"
# define LIGHT_CYAN		"\033[1;36m"
# define BLUE			"\033[1;34m"

typedef struct s_token
{
	char			*command;
	char			**args;
	char			**flags;
	char			separate;
	int				pipe[2];
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_list_hist
{
	char				*string;
	struct s_list_hist	*prev;
	struct s_list_hist	*next;
}						t_list_hist;

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
}					t_cursor;

typedef struct s_flags
{
	int			single;
	int			twice;
}				t_flags;

typedef struct s_all
{
	t_list			*env;
	t_list			*test;
	t_token			*token;
	t_term			term;
	t_cursor		cursor;
	t_flags			quote;
	struct termios	terminal;
	int				fd;
	int				flag;
	t_list_hist		*hist;
	char			*old_string;
	char			*string;
	char			*static_home;
	///////test//////////
	int				pipe[2];
	int				oldpipe[2];
	// int				pid;
	int				in;
	int				out;
}					t_all;

void		handle_sigint(int sig);
void		write_minishell(void);
void		ctrl_d_exit(t_all *all);
void		write_minishell(void);
int			ft_putchar(int c);
void		clear_buf(char **buf);
void		main_loop(t_all *all);
int			check_key(char *str, t_all *all);
int			check_key2(char *str, t_all *all);
int			parse_string(t_all *all);
void		delete_from_array(int i, char *str);
t_token		*create_new_token(t_token *token);
int			single_quote_start(int start, char *str);
int			double_quote_start(int start, t_all *all);
int			ecranisation(int start, char *str);
int			skip_space(int start, char *str);
void		string_to_lower(char **mas);
int			ft_pwd(void);
void		get_save_env(t_all *all, char **envp);
void		printf_env(t_all *all);
char		*env_srh_edit(t_list **head, char *need,
				char *changes);
t_list		*env_srh(t_all	*all, char *need);
void		exec(t_all *all);
char		**env_join(t_list *env);
char		*verify_dir(char *path, char *cmd);
void		free_array(char ***mas);
t_list_hist	*create_new_list(t_list_hist *hist);
void		export(t_all *all);
void		sort_export(t_list *export);
void		error_message(char *message, t_all *all);
void		clear_token(t_all *all);
void		env_add(t_all *all, char *need, char *content);
void		cd(t_all *all);
void		terminal(t_all *all);
void		print_export(t_list *all);
void		terminal_off(t_all *all);
void		refresh_cursor(t_all *all, int pos);
int			search_command(t_all *all, int start);
void		get_save_env_test(t_all *all, char **envp);
char		**env_join_test(t_list *env);
char		**separation_line(char *line);
t_list		*copy_list(t_list *env);
void		ft_uset(t_all *all);
void		manager_cmd(t_all *all);
int			fill_command(t_all *all, int i);
int			fill_args(t_all *all, int start);
int			check_syntax(t_all *all, int i);
int			check_semicolons(char *str, int i, t_all *all);
int			check_redirect_in_file(char *str, int i, t_all *all);
int			check_redirect_from_file(char *str, int i, t_all *all);
int			check_pipe(char *str, int i, t_all *all);
void		insert_inside(char *str, int pos, t_all *all, int flag);
char		*parse_dollar(char *str, int i, t_all *all);
void		ft_echo(t_all *all);

void	ft_pipe(t_all *all);
void	fd_close(int fd);

#endif