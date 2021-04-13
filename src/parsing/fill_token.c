/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:52:52 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/13 03:57:48 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (skip_space(i));		// УБЕДИТЬСЯ ЧТО ЭТО НУЖНАЯ ДИЧЬ
		else if(g_string[i] == ';' || g_string[i] == '<'
			|| g_string[i] == '>')
		{
			all->token->separate = *ft_strchr(";><", g_string[i]);
			if (g_string[i + 1] == '>' && g_string[i] == '>')
			{
				i++;
				all->token->separate = 'r';
			}
			return (i);
		}
		else
			i++;
	}
	return (i);
}

int		fill_command(t_all *all, int i)
{
	int j;

	if (!ft_strchr("<>;|", g_string[i]))
	{
		j = i;
		i = search_command(all, i);
		if (i == j)
			i++;
		all->token->command = ft_substr(g_string, j, i - j);
		if (ft_strchr("<>;|", g_string[i]))
			all->token->separate = *ft_strchr("<>;", g_string[i]);
		if (all->token->separate == '>' && g_string[i + 1] == '>')
				all->token->separate = 'r';
		string_to_lower(&all->token->command);
	}
	else
	{
		all->token->separate = *ft_strchr("<>;|", g_string[i]);
		if (g_string[i] == '>' && g_string[i + 1] == '>')
		{
			i++;
			all->token->separate = 'r';
		}
	}
	return (skip_space(i));
}

int		fill_args(t_all *all, int start)
{
	int	j;
	int k;

	k = 0;
	if (ft_strchr("><;|\n", g_string[start]))
		start++;
	while (!ft_strchr("><;|\n\0", g_string[start]))
	{
		skip_space(start);
		j = search_command(all, start);
		all->token->args[++k] = ft_substr(g_string, start, j - start);
		start = j;
	}
	all->token->args[++k] = NULL;
	if (ft_strchr("><;|\n", g_string[start]))
		all->token->separate = *ft_strchr("><;|\n", g_string[start]);
	return (start);
}

int		search_flags(t_all *all, int start)
{
	return (start);
}