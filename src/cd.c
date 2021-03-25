#include "minishell.h"

void	cd(t_list **env, char *arg)
{
	chdir(arg);
	char **line;//есть лик от line
	t_list *head;

	head = *env;
	line = env_srh(&head, "USER=");
	printf("%s\n", *line);
	*line = "qqq";
	printf_env(*env);
}