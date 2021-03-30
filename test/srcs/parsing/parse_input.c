/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/30 15:30:40 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int		search_command(t_all *all, int start)
{
	
}

int		search_flags(t_all *all, int start)
{
	return (start);
}

void	parse_string(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (g_string[i] && g_string[i] != '\n')
	{
		i = search_command(all, i);
		i = search_flags(all, i);
		i = search_args(all, i);
		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
	}
}