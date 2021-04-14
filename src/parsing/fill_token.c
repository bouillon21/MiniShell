/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:52:52 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/14 03:39:41 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_command(t_all *all, int start)
{
	char	*tmp;
	int		i;

	i = start;
	while (all->string[i] != '\n')
	{
		if (all->string[i] == '\'')
			i = single_quote_start(i, all->string);
		else if (all->string[i] == '\"')
			i = double_quote_start(i, all->string);
		else if (all->string[i] == '\\')
			i = ecranisation(i);
		else if (all->string[i] == ' ')
			return (skip_space(i, all->string));		// УБЕДИТЬСЯ ЧТО ЭТО НУЖНАЯ ДИЧЬ
		else if(all->string[i] == ';' || all->string[i] == '<'
			|| all->string[i] == '>')
		{
			all->token->separate = *ft_strchr(";><", all->string[i]);
			if (all->string[i + 1] == '>' && all->string[i] == '>')
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

	if (!ft_strchr("<>;|", all->string[i]))
	{
		j = i;
		i = search_command(all, i);
		if (i == j)
			i++;
		all->token->command = ft_substr(all->string, j, i - j);
		if (ft_strchr("<>;|", all->string[i]))
			all->token->separate = *ft_strchr("<>;|", all->string[i]);
		if (all->token->separate == '>' && all->string[i + 1] == '>')
				all->token->separate = 'r';
		string_to_lower(&all->token->command);
	}
	else
	{
		all->token->separate = *ft_strchr("<>;|", all->string[i]);
		if (all->string[i] == '>' && all->string[i + 1] == '>')
		{
			i++;
			all->token->separate = 'r';
		}
	}
	return (skip_space(i, all->string));
}

int		fill_args(t_all *all, int start)
{
	int	j;
	int k;

	k = 0;
	if (ft_strchr("><;|\n", all->string[start]))
		start++;
	while (!ft_strchr("><;|\n\0", all->string[start]))
	{
		skip_space(start, all->string);
		j = search_command(all, start);
		all->token->args[++k] = ft_substr(all->string, start, j - start);
		start = j;
	}
	all->token->args[++k] = NULL;
	if (ft_strchr("><;|\n", all->string[start]))
		all->token->separate = *ft_strchr("><;|\n", all->string[start]);
	return (start);
}

int		search_flags(t_all *all, int start)
{
	return (start);
}