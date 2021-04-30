/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:40:59 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/30 21:39:24 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_cursor(t_all *all, int pos)
{
	all->cursor.start_pos = 0;
	all->cursor.end_pos = pos;
	all->cursor.current_pos = pos;
}

void	build_string(t_all *all, char *str)
{
	char	*tmp;
	int		len;

	len = ft_strlen(str);
	all->cursor.end_pos += write(1, str, len);
	all->cursor.current_pos += len;
	if (all->cursor.current_pos != all->cursor.end_pos)
		insert_inside(str, all->cursor.current_pos - len, all, 1);
	else
	{
		tmp = all->string;
		all->string = ft_strjoin(all->string, str);
		free(tmp);
	}
	if (all->flag == 0)
	{
		free(all->old_string);
		all->old_string = ft_strdup(all->string);
	}
}

void	add_history(t_all *all)
{
	char	*tmp;

	all->in = -1;
	all->out = -1;
	if (all->string[ft_strlen(all->string) - 1] != '\n')
	{
		tmp = all->string;
		all->string = ft_strjoin(all->string, "\n");
		free(tmp);
	}
	write(all->fd, all->string, ft_strlen(all->string));
	if (all->hist->next)
		while (all->hist->next)
			all->hist = all->hist->next;
	all->hist->string = ft_strdup(all->string);
	if (!all->hist->next)
		all->hist->next = create_new_list(all->hist);
	all->hist = all->hist->next;
}

void	read_input(t_all *all)
{
	char	*str;

	while (1)
	{
		str = ft_calloc(4096, 1);
		read(0, str, 100);
		if (!check_key(str, all))
			build_string(all, str);
		if (ft_strchr(str, '\n'))
		{
			clear_buf(&str);
			break ;
		}
		clear_buf(&str);
	}
}

void	main_loop(t_all *all)
{
	while (1)
	{
		terminal(all);
		refresh_cursor(all, 0);
		write_minishell();
		all->string = ft_calloc(100, 1);
		if (!all->string)
			exit (errno);
		all->string[0] = 0;
		all->old_string = ft_calloc(100, 1);
		read_input(all);
		write(1, "\n", 1);
		free(all->old_string);
		if (all->string[0] != 0)
			launch_command(all);
		else
			clear_buf(&all->string);
	}
}
