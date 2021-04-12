/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/12 21:09:32 by hmickey          ###   ########.fr       */
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

int		search_flags(t_all *all, int start)
{
	return (start);
}

int		fill_args(t_all *all, int start, int *k)
{
	int	j;
	skip_space(start);
	j = search_command(all, start);
	all->token->args[++(*k)] = ft_substr(g_string, start, j - start);
	return (j);
}

int		count_args(t_all *all, int i)
{
	int flag;
	int words;

	words = 2;
	flag = 0;
	while (g_string[i])
	{
		if (g_string[i] == '\"' && flag == 0)
			flag = 1;
		else if (g_string[i] == '\'' && flag == 0)
			flag = 2;
		else if (ft_strchr(";\n\0", g_string[i]) && flag == 0)
			break ;
		else if (g_string[i] == '\"' && flag == 1)
			flag = 0;
		else if (g_string[i] == '\'' && flag == 2)
			flag = 0;
		else if(g_string[i] == ' ' && flag == 0)
		{
			while (g_string[i] == ' ')
				i++;
			if (ft_strchr(";\n\0", g_string[i]))
				break;
			i--;
			words++;
		}
		i++;
	}
	if (flag != 0)
	{
		error_message("Quotes are not closed", all);
		return (-1);
	}
	return (words);
}

int		write_command(t_all *all, int i)
{
	int j;

	if (!ft_strchr("<>", g_string[i]))
	{
		j = i;
		i = search_command(all, i);
		if (i == j)
			i++;
		all->token->command = ft_substr(g_string, j, i - j);
		string_to_lower(&all->token->command);
		if (!ft_strncmp(all->token->command, "exit", 4)) // DONT FORGET TO REMOVE THIS!!!!!!!!!!!!!!!!!!
		{
			write(1, "exit\n", 5);
			exit (1);
		}
	}
	return (i);
}

int		parse_string(t_all *all)
{
	int i;
	int k;
	t_token	*head;

	head = all->token;
	i = 0;
	while (g_string[i] != '\0' && g_string[i] != '\n')
	{
		i = skip_space(i);
		k = count_args(all, i);
		if (k == -1)
			return (0);
		all->token->args = ft_calloc(sizeof(char*), k);
		all->token->args[0] = ft_strdup("minishell");
		k = 0;
		i = write_command(all, i);
		if (!all->token->separate)
		{
			i = skip_space(i);
			// i = search_flags(all, i);
			while (g_string[i] != ';' && g_string[i] != '\n')
				i = fill_args(all, i, &k);
		}
		i++;
		all->token->args[++k] = NULL;
		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
	}
	all->token = head;
	return (1);
}