/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:17:10 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/14 21:40:06 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal(t_all *all)
{
	tcgetattr(0, &all->terminal);
	all->terminal.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(0, TCSANOW, &all->terminal);
	all->term.termtype = getenv("xterm-256color");
	all->term.tgetent = tgetent(0, all->term.termtype);
}

void	terminal_off(t_all *all)
{
	tcgetattr(0, &all->terminal);
	all->terminal.c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(0, TCSANOW, &all->terminal);
	all->term.termtype = getenv("xterm-256color");
	all->term.tgetent = tgetent(0, all->term.termtype);
}

void	error_message(char *message, t_all *all)
{
	write(1, RED, ft_strlen(RED));
	ft_putstr_fd("minishell: ", 1);
	write(1, YELLOW, ft_strlen(YELLOW));
	if (all->token->command)
	{
		ft_putstr_fd(all->token->command, 1);
		write(1, ": ", 2);
	}
	write(1, LIGHT_CYAN, ft_strlen(LIGHT_CYAN));
	ft_putstr_fd(message, 1);
	write(1, " 🐒\n", ft_strlen(" 🐒\n"));
	write(1, RESET, ft_strlen(RESET));
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
	if (ret == 0)
		write(all->fd, "\n", 1);
}

int main(int argc, char **argv, char **envp)
{
	t_all all;
	all.env = NULL;

	all.flag = 0;
	all.token = create_new_token(0);
	all.hist = create_new_list(0);
	minishell_history(&all);
	get_save_env(&all, envp);
	signal(SIGINT, handle_sigint);
	main_loop(&all);
}