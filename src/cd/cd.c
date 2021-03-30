#include "minishell.h"

void	cd(t_list **env, char *arg)
{
	chdir(arg);
	printf("%s\n", strerror(errno));
	// char *line;

	// line = *env_srh(env, "USER=");
	// printf("%s\n", line);
	// line = "qqq";
	// printf_env(*env);
}