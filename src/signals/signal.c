/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:43:17 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/12 16:01:20 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	pid_t	pid;
	int status;
	
	pid = waitpid(-1, &status, WNOHANG);
	if (status != 0)
		write(1, "\n", 1);
}

void	ctrl_d_exit(t_all *all)
{
	pid_t	pid;
	int status;

	pid = waitpid(-1, &status, WNOHANG);
	clear_buf(&g_string);
	write(1, YELLOW, ft_strlen(YELLOW));
	write(1, "e", 1);
	write(1, LIGHT_GREEN, ft_strlen(LIGHT_GREEN));
	write(1, "x", 1);
	write(1, LIGHT_CYAN, ft_strlen(LIGHT_CYAN));
	write(1, "i", 1);
	write(1, BLUE, ft_strlen(BLUE));
	write(1, "t", 1);
	if (status != 0)
		write(1, "\n", 1);
	terminal_off(all);
	write (1, RESET, ft_strlen(RESET));
	exit(1);
}