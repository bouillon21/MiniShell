/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/30 17:53:48 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int		search_command(t_all *all, int start)
{
	char	*tmp;
	int		i;

	i = start;
	while (g_string[i])
	{
		if (g_string[i] == '\'')
			i = single_quote_start(i);
		else if (g_string[i] == '\"')
			i = double_quote_start(i);
		else if (g_string[i] == '\\')
			i = ecranisation(i);
		else if (g_string[i] == ' ')
			check_leftovers(i);
		else if(g_string[i] == ';' || g_string[i] == '>'
			|| g_string[i] == '>')
			;
		else
			i++;
	}
	return (start);
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
		// i = search_command(all, i);
		// i = search_flags(all, i);
		// i = search_args(all, i);
		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
	}
}