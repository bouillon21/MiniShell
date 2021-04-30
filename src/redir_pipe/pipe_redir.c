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

void	redir(t_all *all)
{
	if (all->token->separate == 'r')
	{
		if (all->out != -1)
			close(all->out);
		all->out = open(all->token->next->args[1],
				O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		if (all->out == -1)
			error_message(strerror(errno), all);
	}
	else if (all->token->separate == '>')
	{
		if (all->out != -1)
			close(all->out);
		all->out = open(all->token->next->args[1],
				O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	}
	else if (all->token->separate == '<')
	{
		if (all->in != -1)
			close(all->in);
		all->in = open(all->token->next->args[1], O_RDONLY, S_IRWXU);
		if (all->in == -1)
			error_message(strerror(errno), all);
	}
}
