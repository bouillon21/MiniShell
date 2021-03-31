/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:43:17 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/31 19:50:42 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	clear_buf(&g_string);
	g_string = malloc(4096);
	write(1, "\n", 1);
	write_minishell();
}

void	ctrl_d_exit(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	write(1, YELLOW, ft_strlen(YELLOW));
	printf("exit");
	exit(0);
}