/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:52:52 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/12 21:53:23 by hmickey          ###   ########.fr       */
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
		{
			delete_from_array(i);
			i = single_quote_start(i);
		}
		else if (g_string[i] == '\"')
		{
			delete_from_array(i);
			i = double_quote_start(i);
		}
		else if (g_string[i] == '\\')
			i = ecranisation(i);
		else if (g_string[i] == ' ')
		{
			skip_space(i);						// НЕ ЗАБЫТЬ УБРАТЬ ОТСЮДА
			return (i);
		}
		else if(g_string[i] == ';' || g_string[i] == '<'
			|| g_string[i] == '>')
		{
			all->token->separate = *ft_strchr(";><", g_string[i]);			//ДОПИСАТЬ ДЛЯ >>
			if (g_string[i + 1] == '>' && g_string[i] == '>')
				all->token->separate = 'r';
			return (i);
		}
		else
			i++;
	}
	return (i);
}