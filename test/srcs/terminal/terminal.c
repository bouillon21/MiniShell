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
	all->cursor.start_pos = ft_strlen("🔥minishell🔥$ ") + 1;
	all->cursor.end_pos = all->cursor.start_pos;
	all->cursor.current_pos = all->cursor.start_pos;
}

void	build_string(char *str, char **tmp)
{
	char *old_string;

	old_string = *tmp;
	*tmp = ft_strjoin(*tmp, str);
	free(old_string);
}

void	pizda(char *str)
{
	printf("%c\n", str[2]);
}

void	main_loop(t_all *all)
{
	char	*str;

	while (1)
	{
		write_minishell();
		all->tmp_string = malloc(100);
		all->tmp_string[0] = 0;
		refresh_cursor(all);
		while(1)
		{
			str = malloc(4000);
			read(0, str, 100);
			if (!check_key(str, all))
			{
				all->cursor.end_pos += write(1, str, ft_strlen(str));
				all->cursor.current_pos += ft_strlen(str);
				build_string(str, &all->tmp_string);
			}
			if (ft_strchr(str, '\n'))
			{
				clear_buf(&str);
				break ;
			}
			clear_buf(&str);
		}
		if (all->tmp_string[0] == 0)
			write(1, "\n", 1);
		printf("%s", all->tmp_string);
		clear_buf(&all->tmp_string);
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