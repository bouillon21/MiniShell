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

#include "minishell.h"

void	refresh_cursor(t_all *all)
{
	all->cursor.start_pos = 0;
	all->cursor.end_pos = 0;
	all->cursor.current_pos = 0;
}

void	build_string(t_all *all, char *str)		//ADD SOME FUNCTIONS TO ADD SYMBOLS WHERE CURRENT CURSOR IS PLACED
{
	char *old_string;

	all->cursor.end_pos += write(1, str, ft_strlen(str));
	all->cursor.current_pos += ft_strlen(str);
	old_string = g_string;
	g_string = ft_strjoin(g_string, str);
	free(old_string);
}

void	build_string2(t_all *all, char *str)
{
	char	*old_string;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_isalnum(str[i]))
		{
			all->cursor.end_pos++;
			all->cursor.current_pos++;
			old_string = g_string;
			g_string = ft_strjoin(g_string, &str[i]);
			free(old_string);	
		}
	}
}

void	main_loop(t_all *all)
{
	char	*str;

	while (1)
	{
		write_minishell();
		refresh_cursor(all);
		// HERE I GONNA NEED FILLED ENV STRUCT
		g_string = malloc(100);
		g_string[0] = 0;
		while(1)
		{
			str = malloc(4096);
			read(0, str, 100);
			if (!check_key(str, all) && !ft_strnstr(str, "\177", ft_strlen(str))
			&& !ft_strnstr(str, "\e[3~", ft_strlen(str)))
				build_string(all, str);
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
			write(all->fd, g_string, ft_strlen(g_string));
			parse_string(all);
			//here will be calling of BULAT FUNCTIONS;
		}
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
	all->term.tgetent = tgetent(0, all->term.termtype);
}