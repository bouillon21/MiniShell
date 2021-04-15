/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/15 05:05:54 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 
**	TODO: fix problem with |____ ;    \n|
*/

int		check_quotes(int i, int flag, char *str)
{
	if (str[i] == '\"' && flag == 0)
		return (1);
	else if (str[i] == '\'' && flag == 0)
		return (2);
	else if (str[i] == '\"' && str[i -1] != '\\'&& flag == 1)
		return (0);
	else if (str[i] == '\'' && flag == 2)
		return (0);
	return (flag);
}

int		count_args(t_all *all, int i)
{
	int flag;
	int words;

	words = 3;
	flag = 0;
	while (all->string[i])
	{
		flag = check_quotes(i, flag, all->string);
		if (ft_strchr(";\n\0", all->string[i]) && flag == 0)
			break ;
		else if(all->string[i] == ' ' && flag == 0)
		{
			while (all->string[i] == ' ')
				i++;
			if (ft_strchr(";><|\n\0", all->string[i]))
				break;
			words++ && i--;
		}
		i++;
	}
	if (flag != 0)
		return (-1);
	return (words);
}

int		parse_string(t_all *all)
{
	int i;
	int k;
	t_token	*head;

	head = all->token;
	i = 0;
	all->string[ft_strlen(all->string) + 1] = '\0';
	if (!check_syntax(all))
		return (0);
	while (all->string[i] != '\0' && all->string[i] != '\n')
	{
		i = skip_space(i, all->string);
		k = count_args(all, i);
		if (k == -1)
		{
			printf("wtf\n");
			return (0);
		}
		all->token->args = ft_calloc(sizeof(char*), k);
		all->token->args[0] = ft_strdup("minishell");
		if (!all->token->prev || !ft_strchr("><r",all->token->prev->separate))
			i = fill_command(all, i);
		if (!i)
			return (0);
		if (!all->token->separate)
		{
			// i = search_flags(all, i);
			i = fill_args(all, i);
		}
		else
			all->token->args[1] = NULL;
		i++;
		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
	}
	all->token = head;
	return (1);
}