/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 08:15:28 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/03 22:14:50 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	write_minishell(void)
{
	write(1, RED, ft_strlen(RED));
	tputs(tigetstr("mb"), 1, ft_putchar);
	write(1, "🔥minishell🔥$ ", ft_strlen("🔥minishell🔥$ "));
	write(1, RESET, ft_strlen(RESET));
	tputs(tigetstr("sc"), 1, ft_putchar);
}

void	clear_buf(char **buf)
{
	if (buf)
		ft_bzero(*buf, ft_strlen(*buf));
	free(*buf);
}

void	insert_inside(char *str, int pos, t_all *all, int flag)
{
	char	*tmp;
	char	*tmp2;
	int		ret_cursor;

	if (pos < 0)
		pos = 0;
	tmp = ft_substr(all->string, 0, pos);
	tmp2 = ft_substr(all->string, pos, ft_strlen(all->string));
	free(all->string);
	all->string = ft_strjoin(tmp, str);
	free(tmp);
	tmp = all->string;
	all->string = ft_strjoin(all->string, tmp2);
	free(tmp);
	free(tmp2);
	if (flag)
	{
		tputs(tigetstr("rc"), 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, all->string, ft_strlen(all->string));
		ret_cursor = ft_strlen(all->string) - pos - 1;
		while (ret_cursor-- > 0)
			tputs(tgetstr("le", 0), 1, ft_putchar);
	}
}
