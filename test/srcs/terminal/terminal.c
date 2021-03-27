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

void	build_string(char *str, char **tmp)
{
	char *old_string;

	old_string = *tmp;
	*tmp = ft_strjoin(*tmp, str);
	free(old_string);
}

void	main_loop(t_all *all)
{
	char	symb;
	char	*str;
	int 	i;
	char	*head;
	char	*tmp;

	while (1)
	{
		i = 0;
		write_minishell();
		symb = 0;
		tmp = malloc(9999);
		str = malloc(9999);
		while(1)
		{
			read(0, str, 100);
			if (!check_key(str))
			{
				// write(1, str, ft_strlen(str)); 
				build_string(str, &tmp);
			}
			if (ft_strchr(str, '\n'))
				break ;
		}
		printf("%s", tmp);
		clear_buf(str);
		clear_buf(tmp);
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