/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:40:59 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/26 11:38:03 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int	check_key(char *str)
{
	if(ft_strnstr(str, "\e[A", ft_strlen(str)))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "up", 3);
		return(1);
	}
	else if (ft_strnstr(str, "\e[B", ft_strlen(str)))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "down", 4);	
		return(1);
	}
	else if (ft_strnstr(str, "\004", ft_strlen(str)))
	{
		ctrl_d_exit();
		return(1);
	}
	else if (ft_strnstr(str, "\177", ft_strlen(str)))
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		return(1);
	}
	return (0);
}

void	main_loop(t_all *all)
{
	char	symb;
	char	*str;
	int 	i;
	char	*head;

	str = malloc(5000);
	while (1)
	{
		i = 0;
		clear_buf(str);
		write_minishell();
		symb = 0;
		while(symb != '\n')
		{
			read(0, str, 100);
			if (!check_key(str))
				write(1, str, ft_strlen(str));
			if (ft_strchr(str, '\n'))
				symb = '\n';
		}
		printf("%s\n", "here is command");
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
}