/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:42:34 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/27 08:49:47 by hmickey          ###   ########.fr       */
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

int		press_backspace(char *str)
{
	if (ft_strnstr(str, "\177", ft_strlen(str)))
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		return(1);
	}
	return (0);
}

int		check_key2(char *str)
{
	press_ctrl_d(str);
	press_backspace(str);
	return (0);
}

