/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:58:24 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/09 00:30:31 by hmickey          ###   ########.fr       */
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
			i = skip_space(i);						// НЕ ЗАБЫТЬ УБРАТЬ ОТСЮДА
			return (i);
		}
		else if(g_string[i] == ';' || g_string[i] == '<'
			|| g_string[i] == '>')
		{
			all->token->separate = *ft_strchr(";><", g_string[i]);			//ДОПИСАТЬ ДЛЯ >>
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
	j = search_command(all, start);
	all->token->args[++(*k)] = ft_substr(g_string, start, j - start);
	return (j);
}

void	parse_string(t_all *all)
{
	int i;
	int j;
	int k;

	k = 1;
	i = 0;


	while (g_string[i] != '\0' && g_string[i] != '\n')
	{
		all->token->args = ft_calloc(sizeof(char*), 500);
		all->token->args[0] = ft_strdup("minishell");		// КОСТЫЛЬ НА ВРЕМЯ
		k = 0;
		i = skip_space(i);
		j = i;
		i = search_command(all, i);
		all->token->command = ft_substr(g_string, j, i - j);
		if (!ft_strncmp(all->token->command, "exit", 4)) // DONT FORGET TO REMOVE
		{
			write(1, "exit\n", 5);
			exit (1);
		}
		if (g_string[i] != ';')
		{
			i = skip_space(i);
			// i = search_flags(all, i);
			while (g_string[i] != ';' && g_string[i] != '\n')
				i = fill_args(all, i, &k);
		}
		else
			i++;

		all->token->next = create_new_token(all->token);
		all->token = all->token->next;
	}
}