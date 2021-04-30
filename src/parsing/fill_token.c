/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:52:52 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/30 19:16:40 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_quotes_dollar(t_all *all, int i)
{
	char	*tmp;

	if (all->string[i] == '\'')
		return (single_quote_start(i, all->string));
	else if (all->string[i] == '\"')
		return (double_quote_start(i, all));
	else if (all->string[i] == '$'
		&& (all->string[i + 1] != '\n' || all->string[i + 1] != ' '))
	{
		delete_from_array(i, all->string);
		tmp = parse_dollar(all->string, i, all);
		if (!tmp)
			tmp = ft_strdup("");
		insert_inside(tmp, i, all, 0);
		i = i + ft_strlen(tmp) - 1;
		free(tmp);
		return (++i);
	}
	return (i);
}

int	parse_tilda(t_all *all, int i)
{
	char	*value;
	int		diff;
	t_list	*tmp;

	tmp = env_srh(all, "HOME");
	delete_from_array(i, all->string);
	if (!tmp)
		value = ft_strdup(all->static_home);
	else
		value = ft_strdup(tmp->content->value);
	insert_inside(value, i, all, 0);
	i += ft_strlen(value) - 1;
	free(value);
	return (i);
}

int	search_command(t_all *all, int start)
{
	while (all->string[start] != '\n')
	{
		if (ft_strchr("\'\"$", all->string[start]))
			start = find_quotes_dollar(all, start);
		else if (all->string[start] == '\\')
		{
			delete_from_array(start, all->string);
			if (all->string[start] == '\n')
			{
				error_message("syntax error near unexpected token `\\", all);
				return (0);
			}
		}
		else if (all->string[start] == '~')
			parse_tilda(all, start);
		else if (all->string[start] == ' ')
			return (skip_space(start, all->string));
		else if (ft_strchr(";><|\n\0", all->string[start]))
			return (start);
		else
			start++;
	}
	return (start);
}

int	fill_command(t_all *all, int i)
{
	int	j;

	if (!ft_strchr("<>;|", all->string[i]))
	{
		j = i;
		i = search_command(all, i);
		if (!i)
			return (0);
		all->token->command = ft_substr(all->string, j, i - j);
		string_to_lower(&all->token->command);
	}
	if (ft_strchr("<>;|", all->string[i]))
		all->token->separate = *ft_strchr("<>;|", all->string[i]);
	if (all->string[i + 1] == '>' && all->token->separate == '>')
	{
		i++;
		all->token->separate = 'r';
	}
	return (skip_space(i, all->string));
}

int	fill_args(t_all *all, int start)
{
	int	j;
	int	k;

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
	if (all->token->separate == '>' && all->string[start + 1] == '>')
		all->token->separate = 'r';
	return (start);
}
