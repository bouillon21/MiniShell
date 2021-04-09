/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:40:59 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/09 01:11:41 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_cursor(t_all *all, int pos)
{
	all->cursor.start_pos = 0;
	all->cursor.end_pos = pos;
	all->cursor.current_pos = pos;
}

void	insert_inside(char *str, int pos)
{
	char	*tmp;
	char	*tmp2;
	int		ret_cursor;

	if (pos < 0)
		pos = 0;
	tmp = ft_substr(g_string, 0, pos);
	tmp2 = ft_substr(g_string, pos, ft_strlen(g_string));
	free(g_string);
	g_string = ft_strjoin(tmp, str);
	free(tmp);
	tmp = g_string;
	g_string = ft_strjoin(g_string, tmp2);
	free(tmp);
	free(tmp2);
	tputs(tigetstr("rc"), 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	write(1, g_string, ft_strlen(g_string));
	ret_cursor = ft_strlen(g_string) - pos - 1;
	while (ret_cursor-- > 0)
		tputs(tgetstr("le", 0), 1, ft_putchar);
}

void	build_string(t_all *all, char *str)
{
	char *tmp;
	int len;

	len = ft_strlen(str);
	all->cursor.end_pos += write(1, str, len);
	all->cursor.current_pos += len;
	if (all->cursor.current_pos != all->cursor.end_pos)
		insert_inside(str, all->cursor.current_pos - len);
	else
	{
		tmp = g_string;
		g_string = ft_strjoin(g_string, str);
		free(tmp);
	}
	if (all->flag == 0)
	{
		free(all->old_string);
		all->old_string = ft_strdup(g_string);
	}
}

void	add_history(t_all *all)
{
	char *tmp;

	if (g_string[ft_strlen(g_string) - 1] != '\n')
	{
		tmp = g_string;
		g_string = ft_strjoin(g_string, "\n");
		free(tmp);
	}
	write(all->fd, g_string, ft_strlen(g_string));
	if (all->hist->next)
		while (all->hist->next)
			all->hist = all->hist->next;
	all->hist->string = ft_strdup(g_string);
	if (!all->hist->next)
		all->hist->next = create_new_list(all->hist);
	all->hist = all->hist->next;
}

void	launch_command(t_all *all)
{
	add_history(all);
	parse_string(all);
	// DONT FORGET TO REPLACE KOSTYL
	all->token = all->token->prev;
	if (ft_strcmp(all->token->command, "env") == 0)
		printf_env(all);
	else
		exec(all->token->args, all, all->token->command);
	all->token = all->token->next;
	clear_token(all);
	all->flag = 0;
	free(g_string);
}

void	read_input(t_all *all)
{
	char	*str;

	while(1)
	{
		str = ft_calloc(4096, 1);
		read(0, str, 100);
		if (!check_key(str, all) && !ft_strnstr(str, "\n", ft_strlen(str)))
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
		g_string = ft_calloc(100, 1);
		if (!g_string)
			exit (errno);
		g_string[0] = 0;
		all->old_string = malloc(100);
		read_input(all);
		write(1, "\n", 1);
		free(all->old_string);
		if ((g_string[0] != 0 && g_string[0] != '\n') || all->flag == 1)
			launch_command(all);
		else
			clear_buf(&g_string);
	}
}