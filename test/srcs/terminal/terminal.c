/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:40:59 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/25 20:11:03 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int	ft_putchar(int c)
{
	return(write(1, &c, 1));
}

void	clear_buf(char *buf)
{
	int i;

	i = -1;
	if (buf)
		while (buf[++i])
			buf[i] = 0;
}

void	write_minishell(void)
{
	write(1, RED, ft_strlen(RED));
	write(1, "minishell$ ", 12);
	write(1, RESET, ft_strlen(RESET));
	tputs(save_cursor, 1, ft_putchar);
}

void	main_loop(void)
{
	char	symb;
	char	str[1024];
	int i;
	char	*head;

	while (1)
	{
		i = 0;
		clear_buf(str);
		write_minishell();
		while(!ft_strchr(str, '\n'))
		{
			i += read(0, str, 100);
			if(ft_strnstr(str, "\e[A", ft_strlen(str)))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, "up", 3);
			}
			else if (ft_strnstr(str, "\e[B", ft_strlen(str)))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1, "down", 4);	
			}
			else
			{
				write(1, str, i);
			}
		}
		write(1, head, i);
		if (ft_strnstr(str, "exit", i))
		{
			write(1, "OK\n", 3);
			exit(0);
		}
	}
}

void	terminal(t_all *all)
{
	struct termios	terminal;
	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~(ECHO);
	terminal.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &terminal);
	all->term.termtype = getenv("xterm-256color");
	all->term.tgetent = tgetent(all->term.termbuf, all->term.termtype);
	signal(SIGINT, handle_sigint);
	main_loop();
}