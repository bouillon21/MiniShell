#include "minishell.h"

void	manager_cmd(t_all *all, int flag)
{
	if (ft_strcmp(all->token->command, "env") == 0)
		printf_env(all);
	else if (ft_strcmp(all->token->command, "export") == 0)
		export(all);
	else if (ft_strcmp(all->token->command, "cd") == 0)
		cd(all);
	else if (ft_strcmp(all->token->command, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(all->token->command, "unset") == 0)
		ft_uset(all);
	else if (ft_strcmp(all->token->command, "echo") == 0)
		ft_echo(all);
	else if (ft_strcmp(all->token->command, "exit") == 0)
		exit (1);
	else if (flag == 1)
		exec(all);
}

void	launch_command(t_all *all)
{
	t_token		*head;

	head = all->token;
	add_history(all);
	if (parse_string(all))
	{
		all->token = head;
		while (all->token)
		{
			redir(all);
			if (all->token->separate && all->token->separate != '\n'
				&& all->token->separate != ';')
			{
				pipe(all->token->pipe);
				if (all->token->command)
					exec(all);
			}
			else
				if (all->token->command)
					manager_cmd(all, 1);
			all->token = all->token->next;
		}
	}
	all->token = head;
	clear_token(all);
}
