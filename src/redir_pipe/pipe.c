#include "minishell.h"

void	fd_close(int fd)
{
	if (fd > 0 && fd != 0 && fd != 1)
		close(fd);
}

void	ft_pipe(t_all *all)
{
	if (all->token->prev == 0)
	{
		dup2(all->token->pipe[1], 1);
		fd_close(all->token->pipe[0]);
		fd_close(all->token->pipe[1]);
	}
	else if (all->token->prev && all->token->next
		&& all->token->separate == '|')
	{
		dup2(all->token->prev->pipe[0], 0);
		dup2(all->token->pipe[1], 1);
		fd_close(all->token->pipe[0]);
		fd_close(all->token->pipe[1]);
		fd_close(all->token->prev->pipe[0]);
		fd_close(all->token->prev->pipe[1]);
	}
	else
	{
		dup2(all->token->prev->pipe[0], 0);
		fd_close(all->token->prev->pipe[0]);
		fd_close(all->token->prev->pipe[1]);
	}
}
