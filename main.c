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

int main(int argc, char **argv, char **envp)
{
	t_all all;
	all.env = NULL;

	all.token = malloc(sizeof(t_token));
	// terminal(&all);
	// signal(SIGINT, handle_sigint);
	get_save_env(&all, envp);
	// sleep(2);
	// printf_env(&all);

	// main_loop(&all);
}