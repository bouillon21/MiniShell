// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/03/23 13:17:10 by hmickey           #+#    #+#             */
// /*   Updated: 2021/03/24 09:53:36 by hmickey          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

void	minishell_history(t_all *all)
{
	int ret;

	ret = 1;
	all->fd = open("minishell_history", O_RDWR |
	O_CREAT, 0755 | O_APPEND);
	if (!all->fd)
		exit(0);			// ПОМЕНЯТЬ НА ОШИБКУ СИСЬКИ-ПИСЬКИ;
	while (ret)
	{
		ret = get_next_line(all->fd, &all->hist.string);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_all all;

	all.token = create_new_token(0);
	minishell_history(&all);
	terminal(&all);
	signal(SIGINT, handle_sigint);
	main_loop(&all);
}