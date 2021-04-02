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

	get_save_env(&all, envp);
	all.token = malloc(sizeof(t_token));
	terminal(&all);
	signal(SIGINT, handle_sigint);
	main_loop(&all);
	// char	*line = ft_strdup("cat");
	// char	**mas = malloc(500);
	// mas[0] = ft_strdup("mini");
	// mas[1] = ft_strdup("tut.c");
	// // mas[2] = NULL;
	// exec(mas, &all, line);
}