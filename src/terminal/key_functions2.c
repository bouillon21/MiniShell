/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:42:34 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/07 15:57:59 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		press_del(char *str, t_all *all)
{
	all->cursor.end_pos--;
	delete_from_array(all->cursor.current_pos);
	tputs(tgetstr("dc", 0), 1, ft_putchar);
	return(1);
}

int		press_backspace(char *str, t_all *all)
{
	if (ft_strnstr(str, "\177", ft_strlen(str)))
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
	return (0);
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
	if (g_string[0] == 0 && ft_strnstr(str, "\004", ft_strlen(str)))
		ctrl_d_exit(all);
	if(ft_strnstr(str, "\f", ft_strlen(str)))
		return(ctrl_l(all));
	if (g_string[0] != 0 && ft_strnstr(str, "\e[3~", ft_strlen(str)))
		return (press_del(str, all));
	if (g_string[0] != 0
		&& all->cursor.current_pos > all->cursor.start_pos)
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