/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:42:34 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/27 14:48:06 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

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
		all->cursor.cursor_end_pos--;
		all->cursor.cursor_current_pos--;
		delete_symbol(all);
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		return(1);
	}
	return (0);
}

int		check_key2(char *str, t_all *all)
{
	int i;
	
	i = 0;
	if (all->tmp_string[0] == 0)
		i = press_ctrl_d(str);
	if (all->cursor.cursor_current_pos > all->cursor.cursor_start_pos
		&& all->tmp_string[0] != 0)
		i = press_backspace(str, all);
	return (i);
}