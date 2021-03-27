/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 08:15:28 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/27 16:46:20 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int	ft_putchar(int c)
{
	return(write(1, &c, 1));
}

void	write_minishell(void)
{
	write(1, RED, ft_strlen(RED));
	write(1, "🔥minishell🔥$ ", ft_strlen("🔥minishell🔥$ "));
	write(1, RESET, ft_strlen(RESET));
	tputs(save_cursor, 1, ft_putchar);
}

void	clear_buf(char **buf)
{
	int i;

	i = -1;
	if (buf)
		ft_bzero(*buf, ft_strlen(*buf));
	free(*buf);
}