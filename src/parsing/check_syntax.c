/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 04:03:05 by hmickey           #+#    #+#             */
/*   Updated: 2021/04/15 04:19:43 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		remove_double_quotes(char *str, int i)
{
	delete_from_array(i, str);
	while (str[i] != '\"')
	{
		if (str[i] == '\\')
			delete_from_array(i, str);
		delete_from_array(i, str);
		if (str[i] == '\n')
			return (0);
	}
	str[i] = '1';
	return (1);
}

int		remove_quotes(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\n' && str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			delete_from_array(i, str);
			while (str[i] != '\'')
			{
				delete_from_array(i, str);
				if (str[i] == '\n')
					return (0);
			}
			str[i] = '1';
		}
		if (str[i] == '\"')
			if (!remove_double_quotes(str, i))
				return (0);
	}
	return (1);
}

int		validate_syntax(char *str, int i, char symb, t_all *all) // сюда пришел уже следующий элемент от того, что
{																// мы валидируем
	if (symb == '>' && str[i] == '>')
		delete_from_array(i, str);
	if (symb == ';')
	{
		if(!check_semicolons(str, i, all))
			return (0);
	}
	else if(symb == '>')
	{
		if (!check_redirect_in_file(str, i, all))
			return (0);
	}
	else if(symb == '<')
	{
		if (!check_redirect_from_file(str, i, all))
			return (0);
	}
	else if(symb == '|')
	{
		if (!check_pipe(str, i, all))
			return (0);
	}
	return (1);
}

int		check_syntax(t_all *all)
{
	char	*copy;
	int		i;
	char	symb;

	i = 0;
	copy = ft_strdup(all->string);
	if (!remove_quotes(copy))
	{
		error_message("quotes are not closed", all);
		return (0);
	}
	skip_space(i, copy);
	while (copy[i] != '\n')
	{
		symb = 0;
		if (ft_strchr("><;|", copy[i]))
			symb = *ft_strchr("><;|", copy[i]);
		if (symb != 0)
			if (!(validate_syntax(copy, i + 1, symb, all)))
				return (0);
		i++;
	}
	free(copy);
	return (1);
}