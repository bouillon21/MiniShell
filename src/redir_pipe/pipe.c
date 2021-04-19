#include "minishell.h"

void	ft_pipe(t_all *all)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		all->in = fd[0];
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		all->out = fd[1];
		close(fd[1]);
	}
}