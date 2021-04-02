/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:42:34 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/02 15:36:29 by hmickey          ###   ########.fr       */
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

int		press_ctrl_d(char *str)
{
	if (ft_strnstr(str, "\004", ft_strlen(str)))
	{
		ctrl_d_exit();
		return(1);
	}
	return(0);
}

int		press_backspace(char *str, t_all *all)
{
	if (ft_strnstr(str, "\177", ft_strlen(str)))
	{
		all->cursor.end_pos--;
		all->cursor.current_pos--;
		delete_from_array(all->cursor.current_pos);
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		return(1);
	}
	return (0);
}

int		check_key2(char *str, t_all *all)
{
	if (g_string[0] == 0 && ft_strnstr(str, "\004", ft_strlen(str)))
		return (press_ctrl_d(str));
	if (g_string[0] != 0 && ft_strnstr(str, "\e[3~", ft_strlen(str)))
		return (press_del(str, all));
	if (g_string[0] != 0
		&& all->cursor.current_pos > all->cursor.start_pos)
		return (press_backspace(str, all));
	return (0);
}