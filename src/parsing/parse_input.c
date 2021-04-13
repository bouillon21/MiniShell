/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/13 03:52:45 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 
**	TODO: fix problem with |____ ;    \n|
*/

int		check_quotes(int i, int flag)
{
	if (g_string[i] == '\"' && flag == 0)
		return (1);
	else if (g_string[i] == '\'' && flag == 0)
		return (2);
	else if (g_string[i] == '\"' && flag == 1)
		return (0);
	else if (g_string[i] == '\'' && flag == 2)
		return (0);
	return (flag);
}

int		count_args(t_all *all, int i)
{
	int flag;
	int words;

	words = 2;
	flag = 0;
	while (g_string[i++])
	{
		flag = check_quotes(i, flag);
		if (ft_strchr(";\n\0", g_string[i]) && flag == 0)
			break ;
		else if(g_string[i] == ' ' && flag == 0)
		{
			while (g_string[i] == ' ')
				i++;
			if (ft_strchr(";><|\n\0", g_string[i]))
				break;
			words++ && i--;
		}
	}
	if (flag != 0)
	{
		error_message("Quotes are not closed", all);
		return (-1);
	}
	return (words);
}

int		check_syntax(int i, t_all *all)
{
	if (g_string[i] == ';' && (g_string[i - 1] == ';' || g_string[i + 1] == ';'))
		error_message("syntax error near unexpected token `;;\'", all);
	else
		error_message("syntax error near unexpected token `;\'", all);
	return (0);
}

int		parse_string(t_all *all)
{
	int i;
	int k;
	t_token	*head;

	head = all->token;
	i = 0;
	g_string[ft_strlen(g_string) + 1] = '\0';
	while (g_string[i] != '\0' && g_string[i] != '\n')
	{
		i = skip_space(i);
		k = count_args(all, i);
		if (k == -1)
			return (0);
		all->token->args = ft_calloc(sizeof(char*), k);
		all->token->args[0] = ft_strdup("minishell");
		i = fill_command(all, i);
		if (all->token->separate != ';')
		{
			// i = search_flags(all, i);
			i = fill_args(all, i);
		}
		else if (all->token->separate == ';' && !all->token->command)
			return (check_syntax(i, all));
		else
			all->token->args[1] = NULL;
		i++;
		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
	}
	all->token = head;
	return (1);
}