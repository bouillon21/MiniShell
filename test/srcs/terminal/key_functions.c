/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:35:46 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/27 08:53:13 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int		press_left(char *str)
{
	if (ft_strnstr(str, "\e[D", ft_strlen(str)))
	{
		tputs(cursor_left, 1, ft_putchar);
		return (1);
	}
	return(0);
}

int		press_right(char *str)
{
	if (ft_strnstr(str, "\e[C", ft_strlen(str)))
	{
		tputs(cursor_right, 1, ft_putchar);
		return (1);
	}
	return(0);
}

int		press_up(char *str)
{
	if (ft_strnstr(str, "\e[A", ft_strlen(str)))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "up", 3);
		return(1);
	}
	return(0);
}

int		press_down(char *str)
{
	if (ft_strnstr(str, "\e[B", ft_strlen(str)))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "down", 4);
		return(1);
	}
	return(0);
}

int	check_key(char *str)
{
	printf("%s", str);
	press_left(str);
	press_right(str);
	press_up(str);
	press_down(str);
	check_key2(str);
	return (0);
}