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

#include "test.h"

int main(int argc, char **argv, char **envp)
{
	t_all all;

	all.token = malloc(sizeof(t_token));
	terminal(&all);
	signal(SIGINT, handle_sigint);
	main_loop(&all);
}