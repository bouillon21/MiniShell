/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/29 20:44:28 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../test.h"

int		search_quote_close(int i, char symbol)
{
	// if (!symbol)
		return (0);
	// while (g_string[i])
	// {
	// 	i++;
	// 	if (g_string[i] ==)
	// }
}

int		search_command(t_all *all, int start)
{
	int i;
	char *tmp;

	i = start;
	while (g_string[i] != ' ' && g_string[i] != '\n' && g_string[i] != ';')
		i++;
	tmp = ft_substr(g_string, start, i - start);
	//checking and etc;
	all->token->command = tmp;
	return(i);
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
		write(1, all->token->command, ft_strlen(all->token->command));
		write(1, "\n", 1);
		i = search_flags(all, i);
		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
		i++;
	}
}