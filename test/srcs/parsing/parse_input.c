/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/30 21:19:35 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int		search_command(t_all *all, int start)
{
	char	*tmp;
	int		i;

	i = start;
	while (g_string[i] != '\n')
	{
		if (g_string[i] == '\'')
			i = single_quote_start(i);
		else if (g_string[i] == '\"')
			i = double_quote_start(i);
		else if (g_string[i] == '\\')
			i = ecranisation(i);
		else if (g_string[i] == ' ')
			return (i);
		else if(g_string[i] == ';' || g_string[i] == '>'
			|| g_string[i] == '>' || g_string[i] == '\n')
			return (i);
		else
			i++;
	}
	return (i);
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
	while (g_string[i] && g_string[i] != '\n')
	{
		i = skip_space(i);
		j = i;
		i = search_command(all, i);
		all->token->command = ft_substr(g_string, j, i - j);
		i = skip_space(i);
		printf("%s\n", all->token->command);
		if (g_string[i] != ';')
		{
			i++;
			i = skip_space(i);
			printf("\n-------------\n");
			// i = search_flags(all, i);
			// i = search_args(all, i);
		}
		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
	}
}