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

void	launch_command(t_all *all)
{
	if (all->flag != 1)
		write(all->fd, g_string, ft_strlen(g_string));
	else
	{
		write(all->fd, all->hist->string,
		ft_strlen(all->hist->string));
		clear_buf(&g_string);
		g_string = ft_strdup(all->hist->string);
	}
	
	
	if (all->hist->next)
	{
		while (all->hist->next)
			all->hist = all->hist->next;
		all->hist = all->hist->prev;
	}
	if (all->flag != 1)
		all->hist->string = g_string;


	all->hist->next = create_new_list(all->hist);
	all->hist = all->hist->next;
	parse_string(all);
	// DONT FORGET TO REPLACE KOSTYL
	all->token = all->token->prev;
	cd(all);
	// exec(all->token->args, all, all->token->command);
	all->token = all->token->next;
	clear_token(all);
	all->flag = 0;
}

void	read_input(t_all *all)
{
	char	*str;

	while(1)
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
		refresh_cursor(all);
		write_minishell();
		g_string = ft_calloc(100, 1);
		if (!g_string)
			exit (errno);
		g_string[0] = 0;
		read_input(all);
		if ((g_string[0] != 0 && g_string[0] != '\n') || all->flag == 1)
			launch_command(all);
		else
			clear_buf(&g_string);
	}
}