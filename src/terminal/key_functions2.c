/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:42:34 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/09 01:02:32 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		press_up(t_all *all)
{
	int len;

	if (all->hist->prev)
	{
		tputs(tigetstr("rc"), 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		all->hist = all->hist->prev;
		len = ft_strlen(all->hist->string);
		free(g_string);
		if (all->hist->string[len - 1] == '\n')
			g_string = ft_substr(all->hist->string, 0, len - 1);
		else
			g_string = ft_substr(all->hist->string, 0, len);
		refresh_cursor(all, ft_strlen(g_string));
		write(1, g_string, ft_strlen(g_string));
		all->flag = 1;
	}
	return(1);
}

int		press_del(char *str, t_all *all)
{
	all->cursor.end_pos--;
	delete_from_array(all->cursor.current_pos);
	tputs(tgetstr("dc", 0), 1, ft_putchar);
	return(1);
}

int		press_backspace(char *str, t_all *all)
{
	if (g_string[0] != '\0' && g_string[0] != 0 && g_string)
	{
		all->cursor.end_pos--;
		all->cursor.current_pos--;
		delete_from_array(all->cursor.current_pos);
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
	}	
	return(1);
}

int		ctrl_l(t_all *all)
{
	tputs(tgetstr("cl", 0), 1, ft_putchar);
	write(1, "\n", 1);
	write_minishell();
	write(1, g_string, ft_strlen(g_string));
	return (1);
}

int		check_key2(char *str, t_all *all)
{
	if (ft_strnstr(str, "\e[A", ft_strlen(str)))
		return (press_up(all));
	if (g_string[0] == 0 && ft_strnstr(str, "\004", ft_strlen(str)))
		ctrl_d_exit(all);
	if(ft_strnstr(str, "\f", ft_strlen(str)))
		return(ctrl_l(all));
	if (g_string[0] != 0 && ft_strnstr(str, "\e[3~", ft_strlen(str)))
		return (press_del(str, all));
	if (ft_strnstr(str, "\x7f", ft_strlen(str)))
		return (press_backspace(str, all));
	if (ft_strnstr(str, "\003", ft_strlen(str)))
	{
		clear_buf(&g_string);
		write(1, "\n", 1);
		write_minishell();
		g_string = ft_calloc(4096, 1);
		return (1);
	}
	return (0);
}