#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	t_list	*env;
	t_list *head;
	head = env;

	// env = malloc(sizeof(t_list));
	get_save_env(&env, envp);
	// printf_env(env);
	// ft_pwd();
	// cd(&env ,"..");
	// ft_pwd();
	// char **line;
	// line = env_srh(&env, "USER=");
	// printf("%s\n", *line);
	// *line = "qqq";
	// printf_env(env);
	// free(line);
	cd (&env, "");
	while (1)
	{}
}