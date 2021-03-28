/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/28 19:46:52 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

void	parse_string(t_all *all)
{
	int i;

	i = 0;
	while (g_string[i] != ' ' && g_string[i] != '\n')
		i++;
	all->token->command = ft_substr(g_string, 0, i);
	write(1, all->token->command, ft_strlen(all->token->command));
	write(1, "\n", 1);
	all->token->next = create_new_token(all->token);
	all->token = all->token->next;
}