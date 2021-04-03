/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:17:10 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/02 23:08:13 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal(t_all *all)
{
	tcgetattr(0, &all->terminal);
	all->terminal.c_lflag &= ~(ECHO);
	all->terminal.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &all->terminal);
	all->term.termtype = getenv("xterm-256color");
	all->term.tgetent = tgetent(0, all->term.termtype);
}

void	error_message(char *message, t_all *all)
{
	write (1, "\n", 1);
	ft_putstr_fd("🔥minishell🔥 : ", 1);
	ft_putstr_fd(message, 1);
}

void	minishell_history(t_all *all)
{
	int ret;
	t_list_hist *head;

	head = all->hist;
	ret = 1;
	all->fd = open("minishell_history", O_RDWR |
	O_CREAT, 0755 | O_APPEND);
	if (!all->fd)
		error_message("fail to create minishell_history file", all);
	while (ret)
	{
		ret = get_next_line(all->fd, &all->hist->string);
		all->hist->next = create_new_list(all->hist);
		all->hist = all->hist->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_all all;
	all.env = NULL;

	all.token = create_new_token(0);
	all.hist = create_new_list(0);
	minishell_history(&all);
	get_save_env(&all, envp);
	terminal(&all);
	signal(SIGINT, handle_sigint);
	main_loop(&all);
}