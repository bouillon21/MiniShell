/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 08:15:28 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/01 22:31:38 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar(int c)
{
	return(write(1, &c, 1));
}

void	write_minishell(void)
{
	write(1, RED, ft_strlen(RED));
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