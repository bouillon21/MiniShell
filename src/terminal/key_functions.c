/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:35:46 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/01 12:21:58 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		press_left(char *str, t_all *all)
{
	if (ft_strnstr(str, "\e[D", ft_strlen(str)))
	{
		if (all->cursor.current_pos > all->cursor.start_pos)
		{
			all->cursor.current_pos--;
			tputs(tgetstr("le", 0), 1, ft_putchar);
		}
		return (1);
	}
	return(0);
}

int		press_right(char *str, t_all *all)
{
	if (ft_strnstr(str, "\e[C", ft_strlen(str)))
	{
		if (all->cursor.current_pos < all->cursor.end_pos)
		{
			all->cursor.current_pos++;
			tputs(tgetstr("nd", 0), 1, ft_putchar);
		}
		return (1);
	}
	return(0);
}

int		press_up(char *str, t_all *all)
{
	if (ft_strnstr(str, "\e[A", ft_strlen(str)))
	{
		tputs(tigetstr("rc"), 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "up", 3);						// there will be function to read from history
		return(1);
	}
	return(0);
}

int		press_down(char *str, t_all *all)
{
	if (ft_strnstr(str, "\e[B", ft_strlen(str)))
	{
		tputs(tigetstr("rc"), 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "down", 4);					// there will be function to read from history
		return(1);
	}
	return(0);
}

int	check_key(char *str, t_all *all)
{
	int i;

	i = press_left(str, all);
	if (i != 1)
		i = press_right(str, all);
	if (i != 1)
		i = press_up(str, all);
	if (i != 1)
		i = press_down(str, all);
	if (i != 1)
		i = check_key2(str, all);
	return (i);
}