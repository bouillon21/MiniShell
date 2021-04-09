/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 08:35:46 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/09 18:35:56 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		press_left(t_all *all)
{
	if (all->cursor.current_pos > all->cursor.start_pos)
	{
		all->cursor.current_pos--;
		tputs(tgetstr("le", 0), 1, ft_putchar);
	}
	return (1);
}

int		press_right(t_all *all)
{
	if (all->cursor.current_pos < all->cursor.end_pos)
	{
		all->cursor.current_pos++;
		tputs(tgetstr("nd", 0), 1, ft_putchar);
	}
	return (1);
}

void	press_down_end_hist(t_all *all)
{
	tputs(tigetstr("rc"), 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	free(g_string);
	g_string = ft_strdup(all->old_string);
	all->flag = 0;
	write(1, g_string, ft_strlen(g_string));
	refresh_cursor(all, ft_strlen(g_string));
}

int		press_down(t_all *all)
{
	if (all->hist->next)
		all->hist = all->hist->next;
	if (all->hist->string != NULL)
	{
		tputs(tigetstr("rc"), 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		all->flag = 1;
		free(g_string);
		if (all->hist->string[ft_strlen(all->hist->string) - 1] == '\n')
			g_string = ft_substr(all->hist->string, 0,
				ft_strlen(all->hist->string) - 1);
		else
			g_string = ft_strdup(all->hist->string);
		refresh_cursor(all, ft_strlen(all->hist->string));
	}
	else if (all->flag == 1)
		press_down_end_hist(all);
	write(1, all->hist->string, ft_strlen(all->hist->string));
	return(1);
}

int	check_key(char *str, t_all *all)
{
	if (ft_strnstr(str, "\n", ft_strlen(str)))
		return (1);
	if (ft_strnstr(str, "\e[D", ft_strlen(str)))
		return (press_left(all));
	if (ft_strnstr(str, "\e[C", ft_strlen(str)))
		return (press_right(all));
	if (ft_strnstr(str, "\e[B", ft_strlen(str)))
		return (press_down(all));
	return (check_key2(str, all));
}