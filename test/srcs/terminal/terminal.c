/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:40:59 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/26 17:56: by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

void	refresh_cursor(t_all *all)
{
	all->cursor.start_pos = 0;
	all->cursor.end_pos = 0;
	all->cursor.current_pos = 0;
}

void	build_string(t_all *all, char *str, char **tmp)		//ADD SOME FUNCTIONS TO ADD SYMBOLS WHERE CURRENT CURSOR IS PLACED
{
	char *old_string;

	all->cursor.end_pos += write(1, str, ft_strlen(str));
	all->cursor.current_pos += ft_strlen(str);
	old_string = *tmp;
	*tmp = ft_strjoin(*tmp, str);
	free(old_string);
}

void	main_loop(t_all *all)
{
	char	*str;

	while (1)
	{
		write_minishell();
		refresh_cursor(all);
		g_string = malloc(100);
		g_string[0] = 0;
		while(1)
		{
			str = malloc(4096);
			read(0, str, 100);
			if (!check_key(str, all))
				build_string(all, str, &g_string);
			if (ft_strchr(str, '\n'))
			{
				clear_buf(&str);
				break ;
			}
			clear_buf(&str);
		}
		if (g_string[0] == 0)
			write(1, "\n", 1);
		else
		{
			// write(1, g_string, ft_strlen(g_string));
			parse_string(all);
		}
		//here will be BULAT FUNCTIONS;
		clear_buf(&g_string);
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