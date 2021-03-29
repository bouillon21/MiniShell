#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	t_list	*env;
	// t_list *head;
	// head = env;

	// env = malloc(sizeof(t_list));
	get_save_env(&env, envp);
	// cd(&env,"/////////bin");
	// ft_pwd();
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
	// cd (&env, "");

	// pid_t forks;
	// forks = fork();
	// int a;
	// if (forks == 0)
	// {
	// 	execve("./minishell", argv, envp);
	// }
	// wait(&a);
	// printf("ya goul");
	exec(argv, env, "ls");
	sleep(1);
	// printf("tut\n");
	while (1)
	{}
}