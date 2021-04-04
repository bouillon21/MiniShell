/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:43:17 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/03 23:01:22 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	clear_buf(&g_string);
	g_string = ft_calloc(4096, 1);
	write(1, "\n", 1);
	// tputs(tgetstr("cb", 0), 1, ft_putchar);
	write_minishell();
}

void	ctrl_d_exit(void)
{
	clear_buf(&g_string);
	write(1, YELLOW, ft_strlen(YELLOW));
	write(1, "e", 1);
	write(1, LIGHT_GREEN, ft_strlen(LIGHT_GREEN));
	write(1, "x", 1);
	write(1, LIGHT_CYAN, ft_strlen(LIGHT_CYAN));
	write(1, "i", 1);
	write(1, BLUE, ft_strlen(BLUE));
	write(1, "t", 1);
	exit(1);
}